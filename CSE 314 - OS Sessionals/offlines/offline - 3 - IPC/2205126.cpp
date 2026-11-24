#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <random>
#include <ctime>
#include <cstdio>
#include <vector>

using namespace std;

int N, M, x, y;
int total_groups;

sem_t stations[4]; 

int group_count[1000]; 
pthread_mutex_t group_mutex[1000]; 
sem_t leader_sem[1000]; 

int read_count = 0;
pthread_mutex_t rw_mutex; 
sem_t rw_sem;             

int operations_completed = 0;
bool all_operations_done = false;

time_t start_time;
pthread_mutex_t console_mutex; 

int get_time() {
    return (int)(time(NULL) - start_time);
}

int get_poisson_random(double lambda) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::poisson_distribution<int> poissonDist(lambda);
    return poissonDist(generator);
}

void* operative_func(void* arg) {
    int id = *(int*)arg; 
    
    int g_id = (id - 1) / M;
    int station_idx = id % 4; 
    bool is_leader = (id % M == 0); 

    int arrival_delay = get_poisson_random(5.0); 
    sleep(arrival_delay);

    pthread_mutex_lock(&console_mutex);
    printf("Operative %d has arrived at typewriting station at time %d\n", id, get_time());
    pthread_mutex_unlock(&console_mutex);

    sem_wait(&stations[station_idx]);
    
    sleep(x); 
    
    pthread_mutex_lock(&console_mutex);
    printf("Operative %d has completed document recreation at time %d\n", id, get_time());
    pthread_mutex_unlock(&console_mutex);
    
    sem_post(&stations[station_idx]);

    pthread_mutex_lock(&group_mutex[g_id]);
    group_count[g_id]++;
    if (group_count[g_id] == M) {
        sem_post(&leader_sem[g_id]); 
    }
    pthread_mutex_unlock(&group_mutex[g_id]);

    if (is_leader) {
        sem_wait(&leader_sem[g_id]);
        
        pthread_mutex_lock(&console_mutex);
        printf("Unit %d has completed document recreation phase at time %d\n", g_id + 1, get_time());
        pthread_mutex_unlock(&console_mutex);

        sem_wait(&rw_sem);
        
        sleep(y); 
        operations_completed++;
        
        pthread_mutex_lock(&console_mutex);
        printf("Unit %d has completed intelligence distribution at time %d\n", g_id + 1, get_time());
        pthread_mutex_unlock(&console_mutex);
        
        sem_post(&rw_sem);
    }

    return NULL;
}

void* staff_func(void* arg) {
    int staff_id = *(int*)arg;
    
    while (!all_operations_done) {
        sleep(get_poisson_random(4.0) + 1); 

        if (all_operations_done) break;

        pthread_mutex_lock(&rw_mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_sem); 
        }
        pthread_mutex_unlock(&rw_mutex);

        pthread_mutex_lock(&console_mutex);
        printf("Intelligence Staff %d began reviewing logbook at time %d. Operations completed = %d\n", 
                  staff_id, get_time(), operations_completed);
        pthread_mutex_unlock(&console_mutex);
                  
        sleep(1); 

        pthread_mutex_lock(&rw_mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_sem); 
        }
        pthread_mutex_unlock(&rw_mutex);
    }
    return NULL;
}

void init_synchronization() {
    for(int i = 0; i < 4; i++) {
        sem_init(&stations[i], 0, 1);
    }
    
    total_groups = N / M;
    for(int i = 0; i < total_groups; i++) {
        group_count[i] = 0;
        pthread_mutex_init(&group_mutex[i], NULL);
        sem_init(&leader_sem[i], 0, 0); 
    }
    
    pthread_mutex_init(&rw_mutex, NULL);
    sem_init(&rw_sem, 0, 1);
    
    pthread_mutex_init(&console_mutex, NULL);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    if (!(cin >> N >> M >> x >> y)) {
        return 0; 
    }

    start_time = time(NULL);
    init_synchronization();

    pthread_t operatives[N];
    int op_ids[N];

    pthread_t staff[2];
    int staff_ids[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        pthread_create(&staff[i], NULL, staff_func, &staff_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        op_ids[i] = i + 1; 
        pthread_create(&operatives[i], NULL, operative_func, &op_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(operatives[i], NULL);
    }

    all_operations_done = true;

    for (int i = 0; i < 2; i++) {
        pthread_join(staff[i], NULL);
    }

    cout << "END" << endl;
    return 0;
}