#ifndef SOLOTEST_H
#define SOLOTEST_H

#endif

#define TOTAL_NODES 33
#define MAX_STACK 100000

class Board {
    private:
        class Node {
            public:
                Node() = default;
                char is_filled;
                Node* left;
                Node* right;
                Node* up;
                Node* down;
        };
        Node* all_nodes[TOTAL_NODES];
        
    public:
        int count_filled();
        int try_move(int, int, int);
        int try_move(Node *, Node*, Node*);
        void print_board();
        int solve(int);

        static void print_board_indices();
        static int get_neighbor_index(int, int, int);

        Board(const Board&);
        Board();
        ~Board();
        Board& operator=(const Board&) = delete;
};