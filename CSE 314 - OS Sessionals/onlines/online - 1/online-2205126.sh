#!/usr/bin/bash

month=$(date +%B)

# echo "$month"
touch a.txt
echo "cd input_dir"
(ls -l) >> a.txt
dest=""
    while IFS= read -r line ; do
        dest=${line//x/""}

        mkdir -p "$(dirname "$dest")"

        cp "$dest" "$dest"
       
    done < (/home/user/Desktop/2205126/C1/a.txt)