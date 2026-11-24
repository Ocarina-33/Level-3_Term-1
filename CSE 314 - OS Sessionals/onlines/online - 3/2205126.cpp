#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int n; 
int current_iter = 1;
int a_count = 0;
int b_count = 0;
int c_count = 0;
int nl = 0;

sem_t a_c;
sem_t sem_nl;
sem_t b_c;
sem_t c_c;
sem_t d_c;

struct ThreadData {
    char letter;
    int* my_count;
};

void* print_letterA(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    char my_letter = data->letter;
    int* my_count = data->my_count;

    while (current_iter<=7) {
        sem_wait(&a_c);
        
       cout << my_letter;
            (*my_count)++; 
        sem_post(&a_c); 


    //    sem_wait(&b_c);
    //    cout << my_letter;
    //         (*my_count)++; 
        
    //     sem_post(&b_c); 

    //      sem_wait(&c_c);
    //    cout << my_letter;
    //         (*my_count)++; 
        
    //     sem_post(&c_c); 
         
          
        current_iter++;

        
        
       // sem_post(&lock);

        usleep(rand() % 500 + 1);
    }
    
    return NULL;
}


void* print_letterB(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    char my_letter = data->letter;
    int* my_count = data->my_count;

    while (current_iter<=7) {
    //     sem_wait(&a_c);
        
    //    cout << my_letter;
    //         (*my_count)++; 
    //     sem_post(&a_c); 


       sem_wait(&b_c);
       cout << my_letter;
            (*my_count)++; 
        
        sem_post(&b_c); 

    //      sem_wait(&c_c);
    //    cout << my_letter;
    //         (*my_count)++; 
        
    //     sem_post(&c_c); 
         
          
        current_iter++;

        
        
       // sem_post(&lock);

        usleep(rand() % 500 + 1);
    }
    
    return NULL;
}

void* print_letterC(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    char my_letter = data->letter;
    int* my_count = data->my_count;

    while (current_iter<=7) {
    //     sem_wait(&a_c);
        
    //    cout << my_letter;
    //         (*my_count)++; 
    //     sem_post(&a_c); 


    //    sem_wait(&b_c);
    //    cout << my_letter;
    //         (*my_count)++; 
        
    //     sem_post(&b_c); 

         sem_wait(&c_c);
       cout << my_letter;
            (*my_count)++; 
        
        sem_post(&c_c); 
         
          
        current_iter++;

        
        
       // sem_post(&lock);

        usleep(rand() % 500 + 1);
    }
    
    return NULL;
}

void* print_newline(void* arg) {
    while (current_iter <= 7) {
        sem_wait(&sem_nl);
        
        if (current_iter > 7) {
            sem_post(&sem_nl);
            break;
        }
    if (a_count == 3 && b_count == 4 && c_count == 5) {
        cout<<endl;
    }
        current_iter++;
        
        sem_post(&sem_nl);
    }
    return NULL;
}

int main() {
    
    srand(time(NULL));

    n=7;
    sem_init(&a_c, 0, 1);
    sem_init(&b_c, 0, 1);
    sem_init(&c_c, 0, 1);

    sem_init(&sem_nl, 0, 0);

    pthread_t t1, t2, t3, t4;

    ThreadData data_A = {'A', &a_count};
    ThreadData data_B = {'B', &b_count};
    ThreadData data_C = {'C', &c_count};


    pthread_create(&t1, NULL, print_letterA, &data_A);
    pthread_create(&t2, NULL, print_letterB, &data_B);
    pthread_create(&t3, NULL, print_letterC, &data_C);
    pthread_create(&t4, NULL, print_newline, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

   // sem_destroy(&lock);

    return 0;
}