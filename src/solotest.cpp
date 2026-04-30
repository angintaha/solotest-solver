#include "solotest.h"

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

int Board::count_filled() {
    int count = 0;
    for (int i = 0; i < TOTAL_NODES; i++) {
        if (all_nodes[i]->is_filled == 'F') count++;
    }
    return count;
}

int Board::try_move(int f, int o, int t) {
    Node *from = all_nodes[f], *over = all_nodes[o], *to = all_nodes[t];
    if (from && over && to &&
        from->is_filled == 'F' &&
        over->is_filled == 'F' &&
        to->is_filled == 'E') {

        from->is_filled = 'E';
        over->is_filled = 'E';
        to->is_filled = 'F';
        return 1;
    }
    return 0;
}

int Board::try_move(Node* from, Node* over, Node* to) {
    if (from && over && to &&
        from->is_filled == 'F' &&
        over->is_filled == 'F' &&
        to->is_filled == 'E') {

        from->is_filled = 'E';
        over->is_filled = 'E';
        to->is_filled = 'F';
        return 1;
    }
    return 0;
}

Board::Board(const Board& board) {
    Node* node_map[TOTAL_NODES];

    for (int i = 0; i < TOTAL_NODES; i++) {
        node_map[i] = new Node();
        *node_map[i] = *(board.all_nodes[i]);
    }

    for (int i = 0; i < TOTAL_NODES; i++) {
        Node* orig = board.all_nodes[i];
        Node* copy = node_map[i];

        for (int j = 0; j < TOTAL_NODES; j++) {
            if (orig->left  == board.all_nodes[j]) copy->left  = node_map[j];
            if (orig->right == board.all_nodes[j]) copy->right = node_map[j];
            if (orig->up    == board.all_nodes[j]) copy->up    = node_map[j];
            if (orig->down  == board.all_nodes[j]) copy->down  = node_map[j];
        }

        all_nodes[i] = copy;
    }
}

Board::~Board() {
    for(int i = 0; i < TOTAL_NODES; i++)
        delete all_nodes[i];
}

Board::Board() {
    int index_map[7][7];
    int idx = 0;

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            index_map[i][j] = -1;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
                Node* node = new Node();
                node->is_filled = 'F';
                node->left = node->right = node->up = node->down = NULL;
                all_nodes[idx] = node;
                index_map[i][j] = idx++;
            }
        }
    }

    all_nodes[16]->is_filled = 'E'; // empty center

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            int id = index_map[i][j];
            if (id == -1) continue;

            Node* n = all_nodes[id];
            if (i > 0 && index_map[i-1][j] != -1) n->up = all_nodes[index_map[i-1][j]];
            if (i < 6 && index_map[i+1][j] != -1) n->down = all_nodes[index_map[i+1][j]];
            if (j > 0 && index_map[i][j-1] != -1) n->left = all_nodes[index_map[i][j-1]];
            if (j < 6 && index_map[i][j+1] != -1) n->right = all_nodes[index_map[i][j+1]];
        }
    }
}

void Board::print_board() {
    int i, j, index = 0;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
                std::cout << all_nodes[index++]->is_filled << "  ";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Board::get_neighbor_index(int current, int delta_row, int delta_col) {
    int map[7][7], i, j, idx = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            map[i][j] = -1;

    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4))
                map[i][j] = idx++;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (map[i][j] == current) {
                int ni = i + delta_row;
                int nj = j + delta_col;
                if (ni >= 0 && ni < 7 && nj >= 0 && nj < 7)
                    return map[ni][nj];
            }
        }
    }
    return -1;
}

int Board::solve(int target) {
    std::stack<Board *> s;

    int remaining = count_filled();
    int iteration = 0;
    int target_pin = target;
    Board* brd_cpd = new Board(*this);
    s.push(brd_cpd);

    while (!s.empty()) { // searching through the state space tree using DFS
        Board* current = s.top();
        s.pop();
        
        remaining = current->count_filled();
        iteration++;
        std::cout << "Iteration " << iteration << ": There are " << remaining <<" pins remaining." << std::endl;

        if (remaining <= target_pin) {
            current->print_board();
            break;
        }

        for(int curr_index = 0; curr_index < TOTAL_NODES; curr_index++) {
            if(current->all_nodes[curr_index]->is_filled == 'F') {
                if(current->all_nodes[curr_index]->right != NULL) {
                    if(current->all_nodes[curr_index]->right->right != NULL) {
                        Board *new_board = new Board(*current);
                        if(new_board->try_move(new_board->all_nodes[curr_index], new_board->all_nodes[curr_index]->right, new_board->all_nodes[curr_index]->right->right)) {
                            s.push(new_board);
                        } else {
                            delete new_board;
                        }
                    }
                }
                if(current->all_nodes[curr_index]->left != NULL) {
                    if(current->all_nodes[curr_index]->left->left != NULL) {
                        Board *new_board = new Board(*current);
                        if(new_board->try_move(new_board->all_nodes[curr_index], new_board->all_nodes[curr_index]->left, new_board->all_nodes[curr_index]->left->left)) {
                            s.push(new_board);
                        } else {
                            delete new_board;
                        }
                    }
                }
                if(current->all_nodes[curr_index]->down != NULL) {
                    if(current->all_nodes[curr_index]->down->down != NULL) {
                        Board *new_board = new Board(*current);
                        if(new_board->try_move(new_board->all_nodes[curr_index], new_board->all_nodes[curr_index]->down, new_board->all_nodes[curr_index]->down->down)) {
                            s.push(new_board);
                        } else {
                            delete new_board;
                        }
                    }
                }
                if(current->all_nodes[curr_index]->up != NULL) {
                    if(current->all_nodes[curr_index]->up->up != NULL) {
                        Board *new_board = new Board(*current);
                        if(new_board->try_move(new_board->all_nodes[curr_index], new_board->all_nodes[curr_index]->up, new_board->all_nodes[curr_index]->up->up)) {
                            s.push(new_board);
                        } else {
                            delete new_board;
                        }
                    }
                }
            }
        }
        delete current;
    }

	while(!s.empty()) { // emptying the stack
        Board* temp = s.top();
        s.pop();
        delete temp;
    }

    return iteration;
}

void Board::print_board_indices() {
    int i, j, index{};
    std::cout << "\nBoard Indexes:" << std::endl;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
                std::cout << std::setw(2) << index++ << " ";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}