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

    if (h.id == 1)
    {
        return diff_storage;
    }
    else if (h.id == 2)
    {
        return (h.w1 * diff_storage) + (h.w2 * diff_side);
    }
    else if (h.id == 3)
    {
        return (h.w1 * diff_storage) + (h.w2 * diff_side) + (h.w3 * diff_extra);
    }
    else if (h.id == 4)
    {
        return (h.w1 * diff_storage) + (h.w2 * diff_side) + (h.w3 * diff_extra) + (h.w4 * diff_captures);
    }

    return diff_storage;
}

pair<int, int> minimax(Board board, int depth, int alpha, int beta, int player, Heuristic h)
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
            int eval = minimax(next, depth - 1, alpha, beta, player, h).second;
            if (eval > max_eval || best_move == -1)
            {
                max_eval = eval;
                best_move = m;
            }
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
            int eval = minimax(next, depth - 1, alpha, beta, player, h).second;
            if (eval < min_eval || best_move == -1)
            {
                min_eval = eval;
                best_move = m;
            }
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

    for (int i = 0; i < games; i++)
    {
        Board b;
        while (!b.isGameOver())
        {
            int move;
            if (b.turn == 0)
                move = minimax(b, depth, -INF, INF, 0, p0).first;
            else
                move = minimax(b, depth, -INF, INF, 1, p1).first;
            b.move(move);
        }
        if (b.bins[6] > b.bins[13])
            w0++;
        else if (b.bins[13] > b.bins[6])
            w1++;
        else
            draws++;
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
    Heuristic h_list[] = {
        {1, 1, 0, 0, 0},
        {2, 10, 2, 0, 0},
        {3, 10, 2, 5, 0},
        {4, 10, 2, 5, 5}};

    int games = 100;
    int depth = 5;
    vector<Result> results;

    cout << "Running 12 base experiments...\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                continue;
            
            cout << "Playing H" << h_list[i].id << " vs H" << h_list[j].id << " ...\n";
            results.push_back(play_match(h_list[i], h_list[j], games, depth));
        }
    }

    save_results(results, "experiment_results.txt", games);
    cout << "\nBase results saved to experiment_results.txt\n\n";

    // WEIGHT VARIATION EXPERIMENTS (vs H1)
    cout << "Running Weight Variation Experiments (10 games each)...\n";
    

    int step = 3; 
    int w_games = 10;
    
    ofstream out("experiment_results.txt", ios::app);
    out << "\n\n";
    out << "              WEIGHT VARIATION EXPERIMENTS (P0 vs H1(P1))                \n";
    out << "-------------------------------------------------------------------------\n\n";
    out << left << setw(8) << "Heur" << setw(20) << "Weights(W1,W2,W3,W4)" 
        << setw(10) << "P0_Wins" << setw(10) << "P1_Wins" 
        << setw(10) << "Draws" << "P0_Win%\n";
    out << string(73, '-') << "\n";

    Heuristic H1 = {1, 1, 0, 0, 0};

    cout << "Testing H2 Variations...\n";
    for (int w1 = 1; w1 <= 10; w1 += step)
    {
        for (int w2 = 1; w2 <= 10; w2 += step)
        {
            Heuristic custom_h2 = {2, w1, w2, 0, 0};
            Result r = play_match(custom_h2, H1, w_games, depth);
            
            string w_str = to_string(w1) + "," + to_string(w2) + ",0,0";
            double rate = (double)r.w0 / w_games * 100.0;
            
            out << left << "H" << setw(7) << r.h0 << setw(20) << w_str
                << setw(10) << r.w0 << setw(10) << r.w1 << setw(10) << r.draws 
                << fixed << setprecision(1) << rate << "%\n";
        }
    }

    cout << "Testing H3 Variations...\n";
    for (int w1 = 1; w1 <= 10; w1 += step)
    {
        for (int w2 = 1; w2 <= 10; w2 += step)
        {
            for (int w3 = 1; w3 <= 10; w3 += step)
            {
                Heuristic custom_h3 = {3, w1, w2, w3, 0};
                Result r = play_match(custom_h3, H1, w_games, depth);
                
                string w_str = to_string(w1) + "," + to_string(w2) + "," + to_string(w3) + ",0";
                double rate = (double)r.w0 / w_games * 100.0;
                
                out << left << "H" << setw(7) << r.h0 << setw(20) << w_str
                    << setw(10) << r.w0 << setw(10) << r.w1 << setw(10) << r.draws 
                    << fixed << setprecision(1) << rate << "%\n";
            }
        }
    }

    cout << "Testing H4 Variations...\n";
    for (int w1 = 1; w1 <= 10; w1 += step)
    {
        for (int w2 = 1; w2 <= 10; w2 += step)
        {
            for (int w3 = 1; w3 <= 10; w3 += step)
            {
                for (int w4 = 1; w4 <= 10; w4 += step)
                {
                    Heuristic custom_h4 = {4, w1, w2, w3, w4};
                    Result r = play_match(custom_h4, H1, w_games, depth);
                    
                    string w_str = to_string(w1) + "," + to_string(w2) + "," + to_string(w3) + "," + to_string(w4);
                    double rate = (double)r.w0 / w_games * 100.0;
                    
                    out << left << "H" << setw(7) << r.h0 << setw(20) << w_str
                        << setw(10) << r.w0 << setw(10) << r.w1 << setw(10) << r.draws 
                        << fixed << setprecision(1) << rate << "%\n";
                }
            }
        }
    }

    out.close();
    cout << "\nAll weight variations appended to experiment_results.txt\n";
    cout << "Simulations complete.\n";

    char choice;
    while (true)
    {
        cout << "Run custom match? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y')
            break;

        int p0_id, p1_id;
        cout << "Enter P0 heuristic (1-4): ";
        cin >> p0_id;
        cout << "Enter P1 heuristic (1-4): ";
        cin >> p1_id;
        cout << "Games: ";
        cin >> games;
        cout << "Depth: ";
        cin >> depth;

        if (p0_id >= 1 && p0_id <= 4 && p1_id >= 1 && p1_id <= 4)
        {
            Result res = play_match(h_list[p0_id - 1], h_list[p1_id - 1], games, depth);
            cout << "Result - P0 Wins: " << res.w0 << ", P1 Wins: " << res.w1
                 << ", Draws: " << res.draws << "\n\n";
        }
        else
        {
            cout << "Invalid heuristic IDs.\n";
        }
    }

    return 0;
}