#!/usr/bin/bash
#alias bvcs="/home/shuvra/CSE214/bvcs-assignment/2205126.sh"

usage() {
    echo "BVCS - Bash Version Control System"
    echo "Usage: bvcs <subcommand> [argumets...]"
    echo "  init    - Initialize a new BVCS repository"
    echo "  add     - Stage files for the next commit"
    echo "  status  - Show the working tree status"
    echo "  commit  - Record changes to the repository"
    echo "  log     - Display Commit history"
    echo "  diff    - Show changes between commits and working tree"
    echo "  restore - Restore working tree files"
    echo "  help    - Print this usage information"
} 

check_repo() {
    if [ ! -d ".bvcs" ]; then
        echo "Error: Not a BVCS repository. Run 'init' first."
        exit 1
    fi
}

init_repo() {
    if [ -d ".bvcs" ]; then
        echo "Error: BVCS repository already exists."
        exit 1
    fi


    mkdir -p .bvcs/objects
    touch .bvcs/staging
    touch .bvcs/log
    touch .bvcs/HEAD

    echo "Initialized empty BVCS repository."
}

add_files() {
    
    if [ "$#" -eq 0 ]; then
        echo "Error: No files specified."
        return 1

    fi

    for file in "$@"; do

        if [ ! -f "$file" ]; then
            echo "Error: '$file' not found."
            continue
        fi

        if grep -qx "$file" .bvcs/staging; then
            echo "Already staged: $file"
            continue
        fi

        echo "$file" >> .bvcs/staging
        echo "Staged: $file"

    done
}

show_status() {
    declare -A file_status

    local staged_list=""
    local modified_list=""
    local untracked_list=""

    if [ -s .bvcs/staging ]; then
        while IFS= read -r file; do
            file_status["$file"]="staged"
            staged_list+="$file"$'\n'
        done < .bvcs/staging
    fi

    local head_id=""

    if [ -s .bvcs/HEAD ]; then
        head_id=$(cat .bvcs/HEAD)
    fi

    if [ -n "$head_id" ] && [ -d ".bvcs/objects/$head_id/files" ]; then
        local prefix=".bvcs/objects/$head_id/files/"

        while IFS= read -r snap_file; do
            local rel_path="${snap_file#$prefix}"

            if [ "${file_status["$rel_path"]}" != "staged" ]; then

                file_status["$rel_path"]="tracked"

                if [ -f "$rel_path" ]; then

                    if ! diff -q "$snap_file" "$rel_path" >/dev/null 2>&1; then
                        file_status["$rel_path"]="modified"
                        modified_list+="$rel_path"$'\n'
                    fi
                else
                    file_status["$rel_path"]="modified"
                    modified_list+="$rel_path"$'\n'
                fi
            fi
        done < <(find "$prefix" -type f)
    fi


    while IFS= read -r work_file; do
        local rel_path="${work_file#./}"

        if [ -z "${file_status["$rel_path"]}" ]; then
            file_status["$rel_path"]="untracked"
            untracked_list+="$rel_path"$'\n'
        fi
    done < <(find . -type f ! -path './.bvcs/*')



    local is_clean=1

    if [ -n "$staged_list" ]; then
        echo "Staged for commit:"
        echo -n "$staged_list"
        echo ""
        is_clean=0
    fi


    if [ -n "$modified_list" ]; then
        echo "Modified (not staged):"
        echo -n "$modified_list" | sort
        echo ""
        is_clean=0
    fi

    if [ -n "$untracked_list" ]; then
        echo "Untracked files:"
        echo -n "$untracked_list" | sort 
        echo ""
        is_clean=0
    fi

    if [ $is_clean -eq 1 ]; then
        echo "Nothing to commit, working tree clean."
    fi

}

do_commit() {
    if [ "$1" != "-m" ] || [ -z "$2" ]; then
        echo "Erros: Commit message required. Use -m \"message\"."
        return 1
    fi

    local message="$2"


    if [ ! -s .bvcs/staging ]; then
        echo "Error: Nothing to commit"
        return 1
    fi

    local log_lines=$(wc -l < .bvcs/log)
    local next_id=$(printf "%04d" $((log_lines + 1)))

    local snap_dir=".bvcs/objects/$next_id"
    mkdir -p "$snap_dir/files"


    local head_id=""
    if [ -s .bvcs/HEAD ]; then
        head_id=$(cat .bvcs/HEAD)
        
        cp -r ".bvcs/objects/$head_id/files/." "$snap_dir/files/"
    fi

    local file_count=0
    while IFS= read -r file; do
        local dest="$snap_dir/files/$file"

        mkdir -p "$(dirname "$dest")"

        cp "$file" "$dest"
        ((file_count++))
    done < .bvcs/staging

    echo "$message" > "$snap_dir/message"

    local current_time=$(date +'%Y-%m-%d %H:%M:%S')
    echo "$current_time" > "$snap_dir/timestamp"

    echo "$next_id|$current_time|$message" >> .bvcs/log
    echo "$next_id" > .bvcs/HEAD

    > .bvcs/staging

    echo "[$next_id] $message"
    echo "$file_count file(s) committed."
 }


 show_log() {

    if [ ! -s .bvcs/log ]; then
        echo "No commits yet."
        return 0
    fi

    tac .bvcs/log | while IFS='|' read -r id timestamp message; do

        echo "commit $id"
        echo "Date: $timestamp"
        echo "Message: $message"
        echo ""

    done
 }

 show_diff() {
    if [ ! -s .bvcs/HEAD ]; then
        echo "Error: No commits yet."
        return 1
    fi

    local head_id
    head_id=$(cat .bvcs/HEAD)
    local snap_dir=".bvcs/objects/$head_id/files"

    if [ "$#" -gt 0 ]; then
        local file="$1"
        local snap_file="$snap_dir/$file"

        if [ ! -f "$snap_file" ]; then
            echo "Error: '$file' is not tracked."
            return 1
        fi

        if diff -q "$snap_file" "$file" >/dev/null 2>&1; then
            echo "$file: no changes."
        else
            diff -u --label "$snap_file" --label "$file" "$snap_file" "$file" || true
        fi

    else 

        while IFS= read -r snap_file; do

            local rel_path="${snap_file#$snap_dir/}"

            if diff -q "$snap_file" "$rel_path" >/dev/null 2>&1; then
                echo "$rel_path: no changes."
            else
                diff -u --label "$snap_file" --label "$rel_path" "$snap_file" "$rel_path" || true 
            fi 
        done < <(find "$snap_dir" -type f | sort)
    fi
 }

restore_file() {
    if [ "$#" -eq 0 ]; then 
        echo "Error: No file speicifed."
        return 1
    fi

    local file="$1"

    if [ ! -s .bvcs/HEAD ]; then 
        echo "Error: No commits yet."
        return 1
    fi

    local head_id
    head_id=$(cat .bvcs/HEAD)
    local snap_file=".bvcs/objects/$head_id/files/$file"

    if [ ! -f "$snap_file" ]; then
        echo "Error: '$file' not found in commit $head_id."
        return 1
    fi



    local confirm
    read -p "Restore '$file' from commit $head_id? [y/N]: " confirm

    if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ]; then 
        mkdir -p "$(dirname "$file")"

        cp "$snap_file" "$file"

        echo "Restored: $file"
    else 
        echo "Aborted."
    fi
}

case "$1" in 
    init) 
        init_repo
        ;;
    help)
        usage
        ;;
    add)
        check_repo
        shift
        add_files "$@"
        ;;
    status)
        check_repo
        show_status
        ;;
    commit)
        check_repo
        shift
        do_commit "$@"
        ;;
    log)
        check_repo
        show_log
        ;;
    diff)
        check_repo
        shift 
        show_diff "$@"
        ;;
    restore)
        check_repo
        shift 
        restore_file "$@"
        ;;
    *) 
        echo "Error: Unknown subcommand '$1'."
        exit 1
        ;;
esac
