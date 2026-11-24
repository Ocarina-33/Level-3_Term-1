#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;
using namespace std::chrono;

typedef long long ll;

 //#define EXPERIMENT_MODE 

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
    tour.reserve(n);
    vector<bool> vis(n, false);

    int curr = 0;
    tour.push_back(curr);
    vis[curr] = true;

    for (int i = 0; i < n - 1; i++) {
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
        tour.push_back(next_city);
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
            
            ll delta = (dist_mat[city_prev][city_j] + dist_mat[city_i][city_next]) - 
                       (dist_mat[city_prev][city_i] + dist_mat[city_j][city_next]);
            
            if (delta <= 0) {
                current_cost += delta;
                generateNeighbor(current_tour, i, j); 
                accepted++;
                
                if (current_cost < best_cost) {
                    best_cost = current_cost;
                    best_tour = current_tour;
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
    
    return {best_tour, best_cost, calculateTourCost(initial_tour, n), total_iters, accepted, worse_accepted};
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


struct Point { double x, y; };

void generateRandomEuclideanGraph(int n, mt19937& rng) {
    uniform_real_distribution<double> coord_dist(0.0, 1000.0);
    vector<Point> cities(n);
    
    for (int i = 0; i < n; i++) {
        cities[i].x = coord_dist(rng);
        cities[i].y = coord_dist(rng);
    }
    
    for (int i = 0; i < n; i++) {
        dist_mat[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            double dx = cities[i].x - cities[j].x;
            double dy = cities[i].y - cities[j].y;
            int dist = round(sqrt(dx * dx + dy * dy)); 
            dist_mat[i][j] = dist;
            dist_mat[j][i] = dist;
        }
    }
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
        
        if (result.best_cost < stats.best_cost) stats.best_cost = result.best_cost;
        if (result.best_cost > stats.worst_cost) stats.worst_cost = result.best_cost;
    }
    
    stats.avg_cost = (double)total_cost / 5.0;
    stats.avg_time = total_time / 5.0;
    return stats;
}

int main() {
    fast

#ifdef EXPERIMENT_MODE

    freopen("output.txt", "w", stdout);
    random_device rd;
    mt19937 rng(rd()); 
    vector<int> test_sizes = {10, 20, 50, 100, 200};

    cout << " TSP EXPERIMENTAL RESULTS REPORT\n";
    cout << "------------------------------------\n\n";

    cout << " a) 18. Experimental Results Table (Exp 1) \n\n";
    cout << left << setw(10) << "Instance" << setw(8) << "Cities" << setw(10) << "Greedy" 
         << setw(10) << "SA Best" << setw(10) << "SA Avg." << setw(14) << "Improve (%)" 
         << setw(12) << "G Time(s)" << setw(12) << "SA Time(s)" << "\n";
    cout << string(86, '-') << "\n";

    for (int i = 0; i < test_sizes.size(); ++i) {
        int n = test_sizes[i];
        generateRandomEuclideanGraph(n, rng);

        auto start_g = high_resolution_clock::now();
        vector<int> greedy_tour = greedyTSP(n);
        ll greedy_cost = calculateTourCost(greedy_tour, n);
        auto stop_g = high_resolution_clock::now();
        duration<double> greedy_time = stop_g - start_g;

        SAStats sa_stats = runSAMultipleTimes(n, 1000.0, 0.995, false, rng);

        double improve_pct = ((double)(greedy_cost - sa_stats.best_cost) / (double)greedy_cost) * 100.0;

        cout << left << "Test " << setw(5) << (i + 1) << setw(8) << n 
             << setw(10) << greedy_cost << setw(10) << sa_stats.best_cost 
             << setw(10) << fixed << setprecision(1) << sa_stats.avg_cost 
             << setw(14) << fixed << setprecision(2) << improve_pct 
             << setw(12) << fixed << setprecision(5) << greedy_time.count() 
             << setw(12) << fixed << setprecision(5) << sa_stats.avg_time << "\n";
    }
    cout << "\n\n";

    int fixed_n = 50;
    generateRandomEuclideanGraph(fixed_n, rng);

    cout << " b) 17.2 Experiment 2: Different Initial Temperatures (Cities: 50, Alpha: 0.995) \n";
    vector<double> temps = {100.0, 1000.0, 5000.0};
    for (double t0 : temps) {
        SAStats stats = runSAMultipleTimes(fixed_n, t0, 0.995, false, rng);
        cout << "T0 = " << left << setw(8) << fixed << setprecision(0) << t0 
             << " | Best: " << setw(6) << stats.best_cost 
             << " | Avg: " << setw(8) << fixed << setprecision(1) << stats.avg_cost 
             << " | Avg Time: " << fixed << setprecision(4) << stats.avg_time << " s\n";
    }
    cout << "\n";

    cout << " c) 17.3 Experiment 3: Different Cooling Rates (Cities: 50, T0: 1000) \n";
    vector<double> alphas = {0.90, 0.95, 0.995};
    for (double alpha : alphas) {
        SAStats stats = runSAMultipleTimes(fixed_n, 1000.0, alpha, false, rng);
        cout << "Alpha = " << left << setw(5) << fixed << setprecision(3) << alpha 
             << " | Best: " << setw(6) << stats.best_cost 
             << " | Avg: " << setw(8) << fixed << setprecision(1) << stats.avg_cost 
             << " | Avg Time: " << fixed << setprecision(4) << stats.avg_time << " s\n";
    }
    cout << "\n";

    cout << " d) 17.4 Experiment 4: Random vs. Greedy Initialization (Cities: 50, T0: 1000, Alpha: 0.995) \n";
    SAStats rand_stats = runSAMultipleTimes(fixed_n, 1000.0, 0.995, false, rng);
    cout << "Random Init -> Best: " << setw(6) << rand_stats.best_cost 
         << " | Worst: " << setw(6) << rand_stats.worst_cost
         << " | Avg: " << setw(8) << fixed << setprecision(1) << rand_stats.avg_cost 
         << " | Avg Time: " << fixed << setprecision(4) << rand_stats.avg_time << " s\n";

    SAStats greedy_stats = runSAMultipleTimes(fixed_n, 1000.0, 0.995, true, rng);
    cout << "Greedy Init -> Best: " << setw(6) << greedy_stats.best_cost 
         << " | Worst: " << setw(6) << greedy_stats.worst_cost
         << " | Avg: " << setw(8) << fixed << setprecision(1) << greedy_stats.avg_cost 
         << " | Avg Time: " << fixed << setprecision(4) << greedy_stats.avg_time << " s\n";

#else

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n = readInput();

    random_device rd;
    mt19937 rng(rd()); 

    auto start_greedy = high_resolution_clock::now();
    vector<int> greedy_tour = greedyTSP(n);
    ll greedy_cost = calculateTourCost(greedy_tour, n);
    auto end_greedy = high_resolution_clock::now();
    duration<double> greedy_time = end_greedy - start_greedy;

    if (!validateTour(greedy_tour, n)) {
        cerr << "Warning: Greedy tour is invalid!\n";
    }

    double T0 = 1000.0;
    double cooling_rate = 0.995;
    double Tmin = 0.001;
    int iters_per_temp = 100;
    int max_iterations = 100000;

    auto start_sa = high_resolution_clock::now();
    vector<int> initial_sa_tour = generateRandomTour(n, rng);
    SAResult sa_result = simulatedAnnealing(initial_sa_tour, T0, cooling_rate, Tmin, iters_per_temp, max_iterations, rng);
    auto end_sa = high_resolution_clock::now();
    duration<double> sa_time = end_sa - start_sa;

    if (!validateTour(sa_result.best_tour, n)) {
        cerr << "Warning: Simulated Annealing best tour is invalid!\n";
    }

    printResults(n, greedy_tour, greedy_cost, greedy_time.count(), initial_sa_tour, sa_result, sa_time.count(), T0, cooling_rate);

#endif

    return 0;
}