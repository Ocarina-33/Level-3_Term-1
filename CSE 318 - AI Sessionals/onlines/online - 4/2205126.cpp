#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;
using namespace std::chrono;

typedef long long ll;

const int MAXN = 501;
int dist_mat[MAXN][MAXN];

int readInput() {
    
    int n;
    if (cin >> n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> dist_mat[i][j];
            }
        }
    }
    return n;
}

bool validateTour(const vector<int>& tour, int n) {
    if (tour.size() != n) return false;
    if (tour[0] != 0) return false;
    
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (visited[tour[i]]) return false;
        visited[tour[i]] = true;
    }
    return true;
}

ll calculateTourCost(const vector<int>& tour, int n) {
    ll cost = 0;
    for (int i = 0; i < n - 1; ++i) {
        cost += dist_mat[tour[i]][tour[i+1]];
    }
    cost += dist_mat[tour[n-1]][tour[0]];
    return cost;
}

void printTour(const vector<int>& tour, int n) {
    for (int i = 0; i < n; ++i) {
        cout << tour[i] << " -> ";
    }
    cout << tour[0] << "\n";
}

vector<int> generateRandomTour(int n, mt19937& rng) {
    vector<int> tour(n);
    for (int i = 0; i < n; ++i) tour[i] = i;
    shuffle(tour.begin() + 1, tour.end(), rng);
    return tour;
}

vector<int> greedyTSP(int n) {
    vector<int> tour;
    tour.resize(n);          
    vector<bool> vis(n, false);

    int curr = 0;
    tour[0] = curr;           
    vis[curr] = true;

    for (int i = 1; i < n; i++) {          
        ll min_dist = __LONG_LONG_MAX__;
        int next_city = -1;

        for (int j = 0; j < n; j++) {
            if (!vis[j] && curr != j) {
                if (dist_mat[curr][j] < min_dist) {
                    min_dist = dist_mat[curr][j];
                    next_city = j;
                }
            }
        }

        tour[i] = next_city;    
        vis[next_city] = true;
        curr = next_city;
    }
    return tour;
}

void generateNeighbor(vector<int>& tour, int i, int j) {
    reverse(tour.begin() + i, tour.begin() + j + 1);
}

struct SAResult {
    vector<int> best_tour;
    ll best_cost;
    ll initial_cost;
    int total_iterations;
    int accepted_moves;
    int worse_accepted;
    int actualReheatCount;
};

SAResult simulatedAnnealing(vector<int> initial_tour, double T0, double cooling_rate, double Tmin, int iters_per_temp, int max_iterations, mt19937& rng) {
    int n = initial_tour.size();
    vector<int> current_tour = initial_tour;
    ll current_cost = calculateTourCost(current_tour, n);
    
    vector<int> best_tour = current_tour;
    ll best_cost = current_cost;
    
    double T = T0;
    int total_iters = 0;
    int accepted = 0;
    int worse_accepted = 0;

    int stagnation = 0;
    int reheatCount = 0;
    
    uniform_real_distribution<double> probability_dist(0.0, 1.0);
    uniform_int_distribution<int> index_dist(1, n - 1);
    
    while (T > Tmin && total_iters < max_iterations) {
        for (int k = 0; k < iters_per_temp; ++k) {
            if (total_iters >= max_iterations) break;
        
            int i = index_dist(rng);
            int j = index_dist(rng);
            while (i == j) {
                j = index_dist(rng);
            }
            if (i > j) swap(i, j);
            
            int city_prev = current_tour[i - 1];
            int city_i    = current_tour[i];
            int city_j    = current_tour[j];
            int city_next = (j == n - 1) ? current_tour[0] : current_tour[j + 1];
            
            ll C_current = dist_mat[city_prev][city_i] + dist_mat[city_j][city_next];
            ll C_new     = dist_mat[city_prev][city_j] + dist_mat[city_i][city_next];

            ll delta = C_new - C_current;

            
            if (delta <= 0) {
                current_cost += delta;
                generateNeighbor(current_tour, i, j); 
                accepted++;
                
                if (current_cost < best_cost) {
                    best_cost = current_cost;
                    best_tour = current_tour;
                    stagnation = 0;
                }
                else{
                    stagnation++;
                }

                if (stagnation >= 5) {        //threshold = S
                    if(reheatCount<=3){
                    T = T0/2;                      
                    current_tour = best_tour;    
                    current_cost = best_cost;
                    stagnation = 0; 
                    } 
                    reheatCount++;  
               }
            } else {
                
                double p = exp(-delta / T);
                if (probability_dist(rng) < p) {
                    current_cost += delta;
                    generateNeighbor(current_tour, i, j);
                    accepted++;
                    worse_accepted++;
                    
                }
            }
            total_iters++;
        }
        T *= cooling_rate;
    }
    
    return {best_tour, best_cost, calculateTourCost(initial_tour, n), total_iters, accepted, worse_accepted, reheatCount};
}

void printResults(int n, const vector<int>& greedy_tour, ll greedy_cost, double greedy_time,
                  const vector<int>& initial_sa_tour, const SAResult& sa_result, double sa_time, double T0, double cooling_rate) {
    
    cout << "========================================\n";
    cout << "TRAVELLING SALESMAN PROBLEM\n";
    cout << "========================================\n";
    cout << "Number of Cities: " << n << "\n\n";

    cout << "---------- GREEDY METHOD ----------\n";
    cout << "Tour:\n";
    printTour(greedy_tour, n);
    cout << "Total Cost: " << greedy_cost << "\n";
    cout << fixed << setprecision(4) << "Execution Time: " << greedy_time << " seconds\n\n";

    cout << "---------- SIMULATED ANNEALING ----------\n";
    cout << "Initial Solution:\n";
    printTour(initial_sa_tour, n);
    cout << "Initial Cost: " << sa_result.initial_cost << "\n";
    cout << "Best Tour Found:\n";
    printTour(sa_result.best_tour, n);
    cout << "Best Cost: " << sa_result.best_cost << "\n";
    cout << "Initial Temperature: " << (int)T0 << "\n";
    cout << "Cooling Rate: " << cooling_rate << "\n";
    cout << "Total Iterations: " << sa_result.total_iterations << "\n";
    cout << "Accepted Moves: " << sa_result.accepted_moves << "\n";
    cout << "Worse Moves Accepted: " << sa_result.worse_accepted << "\n";
    cout << fixed << setprecision(4) << "Execution Time: " << sa_time << " seconds\n\n";

    cout << "---------- COMPARISON ----------\n";
    cout << "Greedy Cost: " << greedy_cost << "\n";
    cout << "Simulated Annealing Cost: " << sa_result.best_cost << "\n";
    cout << "Best Method for This Run:\n";
    if (greedy_cost < sa_result.best_cost) {
        cout << "Greedy produced a better cost.\n";
    } else if (sa_result.best_cost < greedy_cost) {
        cout << "Simulated Annealing produced a better cost.\n";
    } else {
        cout << "Both methods produced the same cost.\n";
    }
    cout << "========================================\n";
}



struct SAStats {
    ll best_cost;
    ll worst_cost;
    double avg_cost;
    double avg_time;
};

SAStats runSAMultipleTimes(int n, double T0, double cooling_rate, bool use_greedy_init, mt19937& rng) {
    SAStats stats;
    stats.best_cost = __LONG_LONG_MAX__;
    stats.worst_cost = 0;
    ll total_cost = 0;
    double total_time = 0;
    
    for (int i = 0; i < 5; ++i) {
        vector<int> init_tour;
        if (use_greedy_init) {
            init_tour = greedyTSP(n);
        } else {
            init_tour = generateRandomTour(n, rng);
        }
        
        auto start = high_resolution_clock::now();
        SAResult result = simulatedAnnealing(init_tour, T0, cooling_rate, 0.001, 100, 100000, rng);
        auto stop = high_resolution_clock::now();
        
        duration<double> time_taken = stop - start;
        total_time += time_taken.count();
        total_cost += result.best_cost;
        cout<<"For iteration "<<i+1<<" reheat_Count: "<<result.actualReheatCount<<endl;

        if (result.best_cost < stats.best_cost) stats.best_cost = result.best_cost;
        if (result.best_cost > stats.worst_cost) stats.worst_cost = result.best_cost;
        
    }
    
    stats.avg_cost = (double)total_cost / 5.0;
    stats.avg_time = total_time / 5.0;
    
    return stats;
}


int main() {
    fast

    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n = readInput();

    random_device rd;
    mt19937 rng(rd()); 
    

        SAStats sa_stats = runSAMultipleTimes(n, 1000.0, 0.995, true, rng);

        
        cout << left << "Test "  <<"best_cost :" <<sa_stats.best_cost <<endl<< "avg_cost :" <<sa_stats.avg_cost <<endl<<"worst_cost :"<< sa_stats.worst_cost << "\n";

        

    
    return 0;
}