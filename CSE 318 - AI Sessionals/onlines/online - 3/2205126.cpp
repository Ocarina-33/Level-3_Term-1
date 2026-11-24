#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Heuristic
{
    int id;
    int w1, w2, w3, w4;
};

struct Board
{
    int bins[14];
    int turn;                                                // 0 for P0, 1 for P1
    int extra_turns[2];
    int captures[2];

    Board()
    {
        for (int i = 0; i < 14; i++)
        {
            bins[i] = 4;
        }
        bins[6] = 0;
        bins[13] = 0;
        turn = 0;
        extra_turns[0] = extra_turns[1] = 0;
        captures[0] = captures[1] = 0;
    }

    bool isGameOver()
    {
        int sum0 = 0, sum1 = 0;
        for (int i = 0; i <= 5; i++)
            sum0 += bins[i];
        for (int i = 7; i <= 12; i++)
            sum1 += bins[i];
        return sum0 == 0 || sum1 == 0;
    }

    void finalize()
    {
        for (int i = 0; i <= 5; i++)
        {
            bins[6] += bins[i];
            bins[i] = 0;
        }
        for (int i = 7; i <= 12; i++)
        {
            bins[13] += bins[i];
            bins[i] = 0;
        }
    }

    bool move(int index)
    {
        if (bins[index] == 0)
            return false;
        if (turn == 0 && (index < 0 || index > 5))
            return false;
        if (turn == 1 && (index < 7 || index > 12))
            return false;

        int stones = bins[index];
        bins[index] = 0;
        int curr = index;

        while (stones > 0)
        {
            curr = (curr + 1) % 14;
            if (turn == 0 && curr == 13)
                continue;
            if (turn == 1 && curr == 6)
                continue;

            bins[curr]++;
            stones--;
        }

        // Check for extra turn
        bool earned_extra = false;
        if (turn == 0 && curr == 6)
        {
            earned_extra = true;
            extra_turns[0]++;
        }
        else if (turn == 1 && curr == 13)
        {
            earned_extra = true;
            extra_turns[1]++;
        }

        // Check for captures
        if (bins[curr] == 1)
        {
            if (turn == 0 && curr >= 0 && curr <= 5)
            {
                int opp = 12 - curr;
                if (bins[opp] > 0)
                {
                    captures[0] += bins[opp] + 1;
                    bins[6] += bins[opp] + 1;
                    bins[curr] = bins[opp] = 0;
                }
            }
            else if (turn == 1 && curr >= 7 && curr <= 12)
            {
                int opp = 12 - curr;
                if (bins[opp] > 0)
                {
                    captures[1] += bins[opp] + 1;
                    bins[13] += bins[opp] + 1;
                    bins[curr] = bins[opp] = 0;
                }
            }
        }

        if (isGameOver())
        {
            finalize();
            return true;
        }

        if (!earned_extra)
            turn = 1 - turn;
        return true;
    }

    vector<int> getValidMoves()
    {
        vector<int> moves;
        int start = (turn == 0) ? 0 : 7;
        int end = (turn == 0) ? 5 : 12;
        for (int i = start; i <= end; i++)
        {
            if (bins[i] > 0)
                moves.push_back(i);
        }
        // sort(moves.begin(), moves.end());
        // vector<int> maxMove = moves;
        // reverse()
        return moves;
    }
};

int evaluate(Board board, int player, Heuristic h)
{
    int my_storage = (player == 0) ? board.bins[6] : board.bins[13];
    int opp_storage = (player == 0) ? board.bins[13] : board.bins[6];

    int my_side = 0, opp_side = 0;
    int my_start = (player == 0) ? 0 : 7;
    int opp_start = (player == 0) ? 7 : 0;

    for (int i = 0; i < 6; i++)
    {
        my_side += board.bins[my_start + i];
        opp_side += board.bins[opp_start + i];
    }

    int my_extra = board.extra_turns[player];
    int opp_extra = board.extra_turns[1 - player];

    int my_captures = board.captures[player];
    int opp_captures = board.captures[1 - player];

    int diff_storage = my_storage - opp_storage;
    int diff_side = my_side - opp_side;
    int diff_extra = my_extra - opp_extra;
    int diff_captures = my_captures - opp_captures;
    
    int hval = diff_storage;

    if (h.id == 1)
    {
        hval = diff_storage;
    }
    else if (h.id == 2)
    {
        hval = (h.w1 * diff_storage) + (h.w2 * diff_side);
    }
    else if (h.id == 3)
    {
        hval = (h.w1 * diff_storage) + (h.w2 * diff_side) + (h.w3 * diff_extra);
    }
    else if (h.id == 4)
    {
        hval = (h.w1 * diff_storage) + (h.w2 * diff_side) + (h.w3 * diff_extra) + (h.w4 * diff_captures);
    }

    return hval;
}

pair<int, int> minimax(Board board, int depth, int alpha, int beta, int player, Heuristic h, vector<pair<int,int>> &mvs, int &nodes)
{
    if (depth == 0 || board.isGameOver())
    {
        return {-1, evaluate(board, player, h)};
    }

    vector<int> moves = board.getValidMoves();
    if (moves.empty())
        return {-1, evaluate(board, player, h)};

    shuffle(moves.begin(), moves.end(), rng);
   
    

    int best_move = -1;

    if (board.turn == player)
    {
        
        int max_eval = -INF;
        for (int m : moves)
        {
            Board next = board;
            next.move(m);
            int eval = minimax(next, depth - 1, alpha, beta, player, h,mvs,nodes).second;
            if (eval > max_eval || best_move == -1)
            {
                max_eval = eval;
                best_move = m;
            }
            mvs.push_back({eval,m});
            nodes++;
            alpha = max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return {best_move, max_eval};
    }
    else
    {
        int min_eval = INF;
        for (int m : moves)
        {
            Board next = board;
            next.move(m);
            int eval = minimax(next, depth - 1, alpha, beta, player, h, mvs,nodes).second;
            if (eval < min_eval || best_move == -1)
            {
                min_eval = eval;
                best_move = m;
            }

            mvs.push_back({eval,m});
            nodes++;

            beta = min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return {best_move, min_eval};
    }
}



pair<int, int> minimax2(Board board, int depth, int alpha, int beta, int player, Heuristic h, vector<pair<int,int>> &mvs, int &nodes)
{
    if (depth == 0 || board.isGameOver())
    {
        return {-1, evaluate(board, player, h)};
    }

    vector<int> moves;
    for(auto m : mvs){
        moves.push_back(m.second);
    }
    if (moves.empty())
        return {-1, evaluate(board, player, h)};


    int best_move = -1;

    if (board.turn == player)
    {
        
        int max_eval = -INF;
        for (int m : moves)
        {
            Board next = board;
            next.move(m);
            int eval = minimax(next, depth - 1, alpha, beta, player, h,mvs,nodes).second;
            if (eval > max_eval || best_move == -1)
            {
                max_eval = eval;
                best_move = m;
            }
            mvs.push_back({eval,m});

            nodes++;
            alpha = max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return {best_move, max_eval};
    }
    else
    {
        int min_eval = INF;
        for (int m : moves)
        {
            Board next = board;
            next.move(m);
            int eval = minimax(next, depth - 1, alpha, beta, player, h, mvs,nodes).second;
            if (eval < min_eval || best_move == -1)
            {
                min_eval = eval;
                best_move = m;
            }

            mvs.push_back({eval,m});
            nodes++;

            beta = min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return {best_move, min_eval};
    }
}

struct Result
{
    int h0, h1, w0, w1, draws;
};

Result play_match(Heuristic p0, Heuristic p1, int games, int depth)
{
    int w0 = 0, w1 = 0, draws = 0;
    int w01 = 0, w11 = 0, draws1 = 0;

    for (int i = 0; i < games; i++)
    {
        vector<pair<int,int>> mx;
        vector<pair<int,int>> mn;

        Board b;
        int nodes=0;
        while (!b.isGameOver())
        {
            int move;
            
            if (b.turn == 0)
                move = minimax(b, depth, -INF, INF, 0, p0, mx, nodes).first;
            else
                move = minimax(b, depth, -INF, INF, 1, p1, mn,nodes).first;
            b.move(move);
        }
        if (b.bins[6] > b.bins[13])
            w0++;
        else if (b.bins[13] > b.bins[6])
            w1++;
        else
            draws++;


        //////
        Board b1;
        int nodes1=0;
        sort(mx.begin(),mx.end());
        reverse(mx.begin(),mx.end());

        sort(mn.begin(),mn.end());

        while (!b1.isGameOver())
        {
            int move;
            
            if (b1.turn == 0)
                move = minimax2(b1, depth, -INF, INF, 0, p0, mx, nodes1).first;
            else
                move = minimax2(b1, depth, -INF, INF, 1, p1, mn, nodes1).first;
            b1.move(move);
        }
        if (b1.bins[6] > b.bins[13])
            w01++;
        else if (b1.bins[13] > b1.bins[6])
            w11++;
        else
            draws1++;

        
    }
    return {p0.id, p1.id, w0, w1, draws};

    
}

void save_results(const vector<Result> &results, string filename, int games)
{
    ofstream out(filename);
    out << left << setw(10) << "P0(1st)" << setw(10) << "P1(2nd)"
        << setw(10) << "P0_Wins" << setw(10) << "P1_Wins"
        << setw(10) << "Draws" << "P0_Win%\n";
    out << string(60, '-') << "\n";

    for (auto r : results)
    {
        double rate = (double)r.w0 / games * 100.0;
        out << left << "H" << setw(9) << r.h0
            << "H" << setw(9) << r.h1
            << setw(10) << r.w0
            << setw(10) << r.w1
            << setw(10) << r.draws
            << fixed << setprecision(1) << rate << "%\n";
    }
    out.close();
}



int main()
{
    Heuristic H1 = {1, 1, 0, 0, 0};
    Heuristic H2 = {2, 10, 2, 0, 0};
    Heuristic H3 = {3, 10, 2, 5, 0};
    Heuristic H4 = {4, 10, 2, 5, 5};

    Heuristic h_list[] = {H1, H2, H3, H4};

    cout << "  Simulate Match \n";


        int p0_id, p1_id, games, depth;
        int p01_id, p11_id, games1, depth1;

        
        cout << "P0 Heuristic (1-4): ";
        cin >> p0_id;
        cout << "P1 Heuristic (1-4): ";
        cin >> p1_id;
        cout << "Number of Games:    ";
        cin >> games;
        cout << "Search Depth:       ";
        cin >> depth;

        Result res = play_match(h_list[p0_id - 1], h_list[p1_id - 1], games, depth);

        cout << "\nSimulation Results :\n";
        cout << "P0 (H" << res.h0 << ") Wins: " << res.w0 << " (" << fixed << setprecision(1) << (double)res.w0 / games * 100.0 << "%)\n";
        cout << "P1 (H" << res.h1 << ") Wins: " << res.w1 << " (" << fixed << setprecision(1) << (double)res.w1 / games * 100.0 << "%)\n";
        cout << "Draws:        " << res.draws << "\n";

    return 0;
}

