#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
typedef long long ll;

int extractGraphNumber(const string& filename) {
    string numStr = "";
    for (char c : filename) {
        if (isdigit(c)) {
            numStr += c;
        }
    }
    return numStr.empty() ? 0 : stoi(numStr);
}

struct Edge {
    int u, v, weight;
};

struct Graph {
    int n, m;
    vector<vector<pair<int, int>>> adj;
    vector<Edge> edges;

    Graph(int numb_vertices, int numb_edges) {
        n = numb_vertices;
        m = numb_edges;
        adj.resize(n + 1);
    }
};

auto currect_time = chrono::steady_clock::now();
auto time_seed = currect_time.time_since_epoch().count();
mt19937 rng(time_seed);

ll calculateCutWeight(const Graph& G, const vector<int>& partition) {
    ll weight = 0;
    for (const auto& e : G.edges) {
        if (partition[e.u] != partition[e.v]) {
            weight += e.weight;
        }
    }
    return weight;
}

double RandomizedMaxCut(const Graph& G, int iterations) {
    ll total_weight = 0;
    uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < iterations; i++) {
        vector<int> partition(G.n + 1);

        for (int v = 1; v <= G.n; v++) {
            partition[v] = dist(rng);
        }
        total_weight += calculateCutWeight(G, partition);
    }

    return (double)total_weight / iterations;
}

pair<ll, vector<int>> GreedyMaxCut(const Graph& G) {
    vector<int> partition(G.n + 1, -1);
    
    vector<ll> sigma_x(G.n + 1, 0), sigma_y(G.n + 1, 0); 

    ll max_w = -1e18;
    int max_u = -1, max_v = -1;
    
    for (const auto& e : G.edges) {
        if (e.weight > max_w) {
            max_w = e.weight;
            max_u = e.u;
            max_v = e.v;
        }
    }

    if (max_u == -1) return {0, partition};

    partition[max_u] = 0; 
    partition[max_v] = 1; 

    for (auto& edge : G.adj[max_u]) {
        sigma_x[edge.first] += edge.second;
    }

    for (auto& edge : G.adj[max_v]) {
        sigma_y[edge.first] += edge.second;
    }

    for (int v = 1; v <= G.n; v++) {
        if (partition[v] == -1) {

            int best_partition;
            if (sigma_y[v] > sigma_x[v]) {
                best_partition = 0; 
            } else {
                best_partition = 1; 
            }

            partition[v] = best_partition;

            for (auto& edge : G.adj[v]) {
                if (best_partition == 0) {
                    sigma_x[edge.first] += edge.second;
                } else {
                    sigma_y[edge.first] += edge.second;
                }
            }
        }
    }
    
    ll result_w = calculateCutWeight(G, partition);
    return {result_w, partition};
}

pair<ll, vector<int>> SemiGreedyMaxCut(const Graph& G, double alpha) {
    vector<int> partition(G.n + 1, -1);
    vector<ll> sigma_x(G.n + 1, 0), sigma_y(G.n + 1, 0);

    ll max_w = -1e18;
    int max_u = -1;
    int max_v = -1;
    for (const auto& e : G.edges) {
        if (e.weight > max_w) {
            max_w = e.weight;
            max_u = e.u;
            max_v = e.v;
        }
    }

    if (max_u == -1) return {0, partition};

    partition[max_u] = 0;
    partition[max_v] = 1;
    for (auto& edge : G.adj[max_u]) {
        sigma_x[edge.first] += edge.second;
    }

    for (auto& edge : G.adj[max_v]) {
        sigma_y[edge.first] += edge.second;
    }

    int assigned = 2;
    while (assigned < G.n) {
        ll w_min = 1e18;
        ll w_max = -1e18;
        vector<pair<int, ll>> candidates;

        for (int v = 1; v <= G.n; v++) {
            if (partition[v] == -1) {
                ll greedy_val = max(sigma_x[v], sigma_y[v]);
                
                w_min = min({w_min, sigma_x[v], sigma_y[v]});
                w_max = max({w_max, sigma_x[v], sigma_y[v]});
                
                candidates.push_back({v, greedy_val});
            }
        }

        double mu = w_min + alpha * (w_max - w_min);
        vector<int> rcl;

        for (auto& cand : candidates) {
            if (cand.second >= mu) {
                rcl.push_back(cand.first);
            }
        }

        if (rcl.empty()) {
            for (int v = 1; v <= G.n; v++) {
                if (partition[v] == -1) {
                    rcl.push_back(v);
                    break;
                }
            }
        }

        uniform_int_distribution<int> dist(0, rcl.size() - 1);
        int selected_v = rcl[dist(rng)];

        int best_partition = (sigma_y[selected_v] > sigma_x[selected_v]) ? 0 : 1;
        partition[selected_v] = best_partition;
        assigned++;

        for (auto& edge : G.adj[selected_v]) {
            if (best_partition == 0) {
                sigma_x[edge.first] += edge.second;
            } else {
                sigma_y[edge.first] += edge.second;
            }
        }
    }

    ll result_w = calculateCutWeight(G, partition);
    return {result_w, partition};
}

pair<ll, int> LocalSearch(const Graph& G, vector<int> partition, ll current_weight) {
    int iterations = 0;
    bool improved = true;

    vector<ll> sigma_x(G.n + 1, 0), sigma_y(G.n + 1, 0);

    for (int u = 1; u <= G.n; u++) {
        for (auto& edge : G.adj[u]) {
            if (partition[edge.first] == 0) {
                sigma_x[u] += edge.second;
            } else {
                sigma_y[u] += edge.second;
            }
        }
    }

    while (improved) {
        improved = false;
        ll best_delta = 0;
        int best_v = -1;

        for (int v = 1; v <= G.n; v++) {
            ll delta = 0;

            if (partition[v] == 0) {
                delta = sigma_x[v] - sigma_y[v];
            } else {
                delta = sigma_y[v] - sigma_x[v];
            }

            if (delta > best_delta) {
                best_delta = delta;
                best_v = v;
            }
        }

        if (best_delta > 0 && best_v != -1) {
            current_weight += best_delta;
            int old_partition = partition[best_v];
            int new_partition = 1 - old_partition;
            partition[best_v] = new_partition;

            for (auto& edge : G.adj[best_v]) {
                if (old_partition == 0) {
                    sigma_x[edge.first] -= edge.second;
                } else {
                    sigma_y[edge.first] -= edge.second;
                }

                if (new_partition == 0) {
                    sigma_x[edge.first] += edge.second;
                } else {
                    sigma_y[edge.first] += edge.second;
                }
            }

            improved = true;
            iterations++;
        }
    }

    return {current_weight, iterations};
}

pair<ll, int> GRASP(const Graph& G, int max_iterations, double alpha) {
    ll best_global_weight = -1e18;

    for (int i = 0; i < max_iterations; i++) {
        pair<ll, vector<int>> semi_result = SemiGreedyMaxCut(G, alpha);

        ll semi_weight = semi_result.first;
        vector<int> partition = semi_result.second;

        pair<ll, int> local_search_result = LocalSearch(G, partition, semi_weight);

        ll local_search_weight = local_search_result.first;

        if (local_search_weight > best_global_weight) {
            best_global_weight = local_search_weight;
        }
    }

    return {best_global_weight, max_iterations};
}

int main() {
    fast
    
    string directory_path = "./set1"; 
    
    if (!std::filesystem::exists(directory_path)) {
        cerr << "ERROR: Directory does not exist: " << directory_path << "\n";
        return 1;
    }

    ofstream csv("2205126.csv");
  
    csv << "Problem,,,Constructive algorithm,,,Local search,,GRASP,,Known best solution or upper bound\n";
    csv << "Name,|V| or n,|E| or m,Simple Randomized or Randomized-1,Simple Greedy or Greedy-1,Semi-greedy-1,Simple local or local-1,,GRASP-1,,\n";
    csv << ",,,,,,No. of iterations,Average value,No. of iterations,Best value,\n";

    map<string, string> known_best = {
        {"g1", "12078"}, {"g2", "12084"}, {"g3", "12077"},
        {"g11", "627"}, {"g12", "621"}, {"g13", "645"},
        {"g14", "3187"}, {"g15", "3169"}, {"g16", "3172"},
        {"g22", "14123"}, {"g23", "14129"}, {"g24", "14131"},
        {"g32", "1560"}, {"g33", "1537"}, {"g34", "1541"},
        {"g35", "8000"}, {"g36", "7996"}, {"g37", "8009"},
        {"g43", "7027"}, {"g44", "7022"}, {"g45", "7020"},
        {"g48", "6000"}, {"g49", "6000"}, {"g50", "5988"}
    };
    
    int files_processed = 0;

    try {
        vector<string> valid_files;
        for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
            string ext = entry.path().extension().string();
            if (ext == ".rud" || ext == ".RUD") {
                valid_files.push_back(entry.path().string());
            }
        }

        sort(valid_files.begin(), valid_files.end(), [](const string& a, const string& b) {
            string nameA = std::filesystem::path(a).stem().string();
            string nameB = std::filesystem::path(b).stem().string();
            return extractGraphNumber(nameA) < extractGraphNumber(nameB);
        });

        for (const string& file_path : valid_files) {
            string name = std::filesystem::path(file_path).stem().string(); 
            
            ifstream infile(file_path);
            if (!infile) {
                cerr << "Could not open " << file_path << "\n";
                continue;
            }
            
            int n, m;
            infile >> n >> m;
            Graph G(n, m);
            
            for (int i = 0; i < m; ++i) {
                int u, v, w;
                infile >> u >> v >> w;
                G.adj[u].push_back({v, w});
                G.adj[v].push_back({u, w});
                G.edges.push_back({u, v, w});
            }
            
            cout << "Processing " << name << " (V=" << n << ", E=" << m << ")..." << flush;
            
            double rand_val = RandomizedMaxCut(G, 100); 
            auto [greedy_val, _g_part] = GreedyMaxCut(G);
            
            double alpha = 0.5;
            auto [semi_greedy_val, sg_part] = SemiGreedyMaxCut(G, alpha);
            
            vector<int> random_part(G.n + 1);
            uniform_int_distribution<int> dist(0, 1);
            for (int v = 1; v <= G.n; v++) {
                random_part[v] = dist(rng);
            }
            ll random_part_weight = calculateCutWeight(G, random_part);
            
            auto [ls_val, ls_iter] = LocalSearch(G, random_part, random_part_weight);
            
            auto [grasp_val, grasp_iter] = GRASP(G, 100, alpha); 
        
            string known_val = known_best.count(name) ? known_best[name] : "N/A";
            
            csv << name << "," << n << "," << m << "," 
                << fixed << setprecision(2) << rand_val << ","
                << greedy_val << "," << semi_greedy_val << ","
                << ls_iter << "," << ls_val << ","
                << grasp_iter << "," << grasp_val << "," 
                << known_val << endl;
                
            cout << " Done!" << endl;

            files_processed++;
        }
    } catch (const std::exception& e) {
        cerr << "\nCRASH DETECTED: " << e.what() << "\n";
    }
    
    csv.close();
    cout << "\nFinished! Processed " << files_processed << " files. Results saved to 2205126.csv." << endl;
    
    return 0;
}