#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double epsilon = 1e-9;

int k;
vector<int> goal_board;

double weight = 1.0;


bool isEqual(double a, double b){
    return abs(a-b) < epsilon;
}


int countInverse(vector<int> v){
    int count = 0;
    int sz = v.size();
    for(int i=0;i<sz-1;i++){
        for(int j = i+1; j<sz;j++){
            if(v[i] && v[j] && (v[i]>v[j])){
            count++;
            }
        }   
    }

    return count;
}

int Solvable(vector<int> v, int k, int b){
    
    int invCount = countInverse(v);
    if(k%2==1){
        if(invCount%2 == 0){
            return 1;
        }
    }

    else{

        if((b%2==0 and invCount%2==1) or (b%2==1 and invCount%2==0)){
            return 1;
        }
    }
    return 0;
}


void printPath(vector<vector<int>> path){

    for(auto v : path){
        for(int i =0;i<k;i++){
            for(int j=0;j<k;j++){
                cout<<v[i*k+j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\n\n";
    }

}



struct node{
    vector<int> v;
    int b;
    int g;
    double h;
    double f;
    vector<int> movement;
};


struct minNode{
    bool operator()(const node* a, const node* b) const{
        if(isEqual(a->f, b->f)){
            return a->h > b->h;
        }

        return a->f > b->f;
    }
};


double calculateHamming(vector<int> v){
    int sz = k*k;
    double dist = 0;
    for(int i =0;i < sz ; i++){
        if(v[i] and goal_board[i] and(v[i] != goal_board[i])){

            dist++;

        }
    }

    return dist;
}


double calculateManhattan(vector<int> v){
    double total = 0;
    int sz = k*k;

    for(int i =0; i< sz; i++){
        int cur_row = i/k;
        int cur_col = i%k;

        int og_row = (v[i] - 1) / k;
        int og_col = (v[i]-1) % k;

        total+= abs(og_row - cur_row) + abs(og_col - cur_col);

    }

    return total;

}

double calculateEuclidean(vector<int> v){
    double total = 0;
    int sz = k*k;

    for(int i =0; i< sz; i++){
        int cur_row = i/k;
        int cur_col = i%k;

        int og_row = (v[i] - 1) / k;
        int og_col = (v[i]-1) % k;

        total+= sqrt(pow(og_row - cur_row, 2) + pow(og_col - cur_col, 2));

    }

    return total;
    
}

double calculateLinearConflict(vector<int> v){
    double total = calculateManhattan(v);
    int numb_con = 0;
    int sz = k*k;
    vector<int> temp = v;

    //row conflict
    for(int i =0; i<sz; i+=k){
        int cur_row = i/k;

        for(int j=i; j< i+ k-1;j++){
            int og_val_j_row = (v[j] -1)/ k;

            for(int m = j+1; m<i+k; m++){
                int og_val_m_row = (v[m] - 1) / k; 
                if(v[j] and v[m] and (cur_row == og_val_j_row) and (cur_row == og_val_m_row) and (v[j]>v[m])){
                   numb_con++;
                }
            }
        }
    }

    //column conflict
    for(int i =0; i<k; i++){
        int cur_col = i;

        for(int j=i; j<sz;j+=k){
            int og_val_j_col = (v[j] -1) % k;

            for(int m = j+k; m<sz; m+=k){
                int og_val_m_col = (v[m] - 1) % k; 
                if(v[j] and v[m] and (cur_col == og_val_j_col) and (cur_col == og_val_m_col) and (v[j]>v[m])){
                    numb_con++;
                }
            }
        }
    }

    total+= 2*(numb_con);
    return total; 
}

double calculateCustom(vector<int> v) {
    //Gaschnig's Heuristic
    
    double swaps = 0;
    vector<int> temp = v;
    int n = k * k;
    while (true) {
        
        bool is_solved = true;
        for (int i = 0; i < n; i++) {
            if (temp[i] != goal_board[i]) {
                is_solved = false; 
                break;             
            }
        }
        
        if (is_solved) {
            break; 
        }

        int zero_idx = -1;
        for (int i = 0; i < n; i++) {
            if (temp[i] == 0) {
                zero_idx = i;
                break;
            }
        }

        if (zero_idx != n - 1) {
            
            int expected_tile = goal_board[zero_idx];
            
            int target_idx = -1;
            for (int i = 0; i < n; i++) {
                if (temp[i] == expected_tile) {
                    target_idx = i;
                    break;
                }
            }
            
            swap(temp[zero_idx], temp[target_idx]);
            swaps++;
        } 
        
        else {
            for (int i = 0; i < n; i++) {
                if (temp[i] != goal_board[i] && temp[i] != 0) {
                    
                    swap(temp[zero_idx], temp[i]);
                    swaps++;
                    break; 
                }
            }
        }
    }

    return swaps;
}


double calculateHeuristic(vector<int> v, int method){
    if(method==1){
        return calculateHamming(v);
    }

    else if(method==2){
        return calculateManhattan(v);
    }

    else if(method==3){
        return calculateEuclidean(v);
    }
    else if(method == 4){
        return calculateLinearConflict(v);
    }
    else if(method == 5){
        return calculateCustom(v);
    }

    return 0;
}


void Astar(vector<int> v, int blank_index, double weight, int method){

    map<vector<int>, int> best_g;

    map<vector<int>, vector<int> > parent_board;


    priority_queue<node*, vector<node*>, minNode> pq;

    int explored_nodes = 0;

    
    
    vector<int> m;
    m.resize(100, 1);

    node* start_node = new node();
    start_node->v = v;
    start_node->b = blank_index;
    start_node->g=0;
    start_node->h = calculateHeuristic(v, method);
    start_node->f = start_node->g + ( weight * start_node->h );
    start_node->movement = m;
    

    pq.push(start_node);
    best_g[v] = 0;


    while(!pq.empty()){
        auto current_node = pq.top(); pq.pop();
        
        explored_nodes++;

        if(current_node->v == goal_board){
            vector<vector<int>> path;
            vector<int> cur = current_node->v;

            while(parent_board.find(cur) != parent_board.end()){
                path.push_back(cur);
                cur = parent_board[cur];
            }

            path.push_back(v);
            reverse(path.begin(), path.end());

            //cout<<"Explored Nodes = "<<explored_nodes<<endl;
            cout << "number of cost = " << current_node->g << "\n";
            printPath(path);

            delete current_node;
            return;
        }

        int b = current_node->b;

        if(b-k>=0){   //up
            int upPos = b-k;
            vector<int> neighbour = current_node->v;

            int val = neighbour[b-k];
            int new_g = val * current_node->movement[val];


            swap(neighbour[b],neighbour[upPos]);
            
            

            auto it = best_g.find(neighbour);

            if(it==best_g.end() or new_g<best_g[neighbour]){
                best_g[neighbour] = new_g;
                parent_board[neighbour] = current_node->v;

                node* newnode = new node();
                newnode->v = neighbour;
                newnode->h = calculateHeuristic(neighbour, method);
                newnode->b = upPos;
                newnode->g = new_g;
                newnode->f = newnode->g + (weight * newnode->h);

                current_node->movement[val]++;
                newnode->movement = current_node->movement;

                pq.push(newnode);
                
            }

        }

        if(b+k < (k*k)){      //Down
            int downPos = b+k;
            vector<int> neighbour = current_node->v;
            
            int val = neighbour[b-k];
            int new_g = val * current_node->movement[val];

            swap(neighbour[b],neighbour[downPos]);
            
            

            auto it = best_g.find(neighbour);
            if(it==best_g.end() or new_g<best_g[neighbour]){
                best_g[neighbour] = new_g;
                parent_board[neighbour] = current_node->v;

                node* newnode = new node();
                newnode->v = neighbour;
                newnode->h = calculateHeuristic(neighbour, method);
                newnode->b = downPos;
                newnode->g = new_g;
                newnode->f = newnode->g + (weight * newnode->h);

                current_node->movement[val]++;
                newnode->movement = current_node->movement;

                pq.push(newnode);
                
            }
        }

        if((b+1)%k != 0){   //right
            int rightPos = b+1;
            vector<int> neighbour = current_node->v;
            int val = neighbour[b-k];
            int new_g = val * current_node->movement[val];

            swap(neighbour[b],neighbour[rightPos]);
            
            

            auto it = best_g.find(neighbour);
            if(it==best_g.end() or new_g<best_g[neighbour]){
                best_g[neighbour] = new_g;
                parent_board[neighbour] = current_node->v;

                node* newnode = new node();
                newnode->v = neighbour;
                newnode->h = calculateHeuristic(neighbour, method);
                newnode->b = rightPos;
                newnode->g = new_g;
                newnode->f = newnode->g + (weight * newnode->h);
                current_node->movement[val]++;
                newnode->movement = current_node->movement;

                pq.push(newnode);
                
            }

        }

        if(b%k != 0){   //left
            int leftPos = b-1;
            vector<int> neighbour = current_node->v;

            int val = neighbour[b-k];
            int new_g = val * current_node->movement[val];

            swap(neighbour[b],neighbour[leftPos]);
            
            
            auto it = best_g.find(neighbour);
            if(it==best_g.end() or new_g<best_g[neighbour]){
                best_g[neighbour] = new_g;
                parent_board[neighbour] = current_node->v;

                node* newnode = new node();
                newnode->v = neighbour;
                newnode->h = calculateHeuristic(neighbour, method);
                newnode->b = leftPos;
                newnode->g = new_g;
                newnode->f = newnode->g + (weight * newnode->h);

                current_node->movement[val]++;
                newnode->movement = current_node->movement;

                pq.push(newnode);
                
            }
        }

        delete current_node;

    }


}



int main(){
    
        int method;
    
        cout<<"Choose Heuristic Method ->";
        cout<<"\n 1. Hamming Distance\n 2. Manhattan Distance\n 3. Euclidean Distance\n 4. Linear Conflict\n 5. Custom Heuristic"<<endl;
        cout<<"Enter your number: ";
        cin>>method;

        cout<<"Weight: ";
        cin>>weight;
    
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    
        
        cin>>k;
    
        int x;
        int b;
        int blank_index;
        int n = k*k;
        vector<int> v(n);
    
        for(int i=0;i<k*k;i++){
                cin>>x;
                v[i] = x;
                if(x==0) {
                    b = k - i/k;
                    blank_index = i;
            }
        }
    
        goal_board.resize(n,0);
    
        for(int i = 1; i<k*k;i++){
            goal_board[i-1]=i;
        }
        
        if(!Solvable(v,k,b)){
            cout<<"Unsolvable puzzle";
        }
        else{
    
            Astar(v,blank_index, weight, method);
            
        }
    
}