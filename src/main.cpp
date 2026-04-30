#include "solotest.h"
#include <iostream>

int main() {
    Board* board = new Board();

    std::cout << "==== SOLO TEST ====" << std::endl;
    std::cout << "Select a game mode:" << std::endl;
    std::cout << "  1 - Play!" << std::endl;
    std::cout << "  2 - Solve the problem" << std::endl;
    std::cout << "\n  Selection (1/2): ";

    int choice;
    std::cin >> choice;

    if (choice == 2) {
        int how_many{};
        while(how_many <= 0) {
            std::cout << "How many pegs (> 0) do you wanna leave on the board? ";
            std::cin >> how_many;
        }
        std::cout << "\nComputer is trying to solve the game..." << std::endl;

        int iteration_count = board->solve(how_many);
        std::cout << "\nThe computer solved the problem in " << iteration_count << " iterations!" << std::endl;

        delete board;
        return 0;
    }
    else if (choice == 1) {
        std::cout << "\nThe indexes on the board are between 0-32." << std::endl;
        std::cout << "To move: Enter three indexes representing FROM/OVER/TO." << std::endl;
        std::cout << "Enter -1 to exit." << std::endl;


        while (1) {
            board->print_board();
            Board::print_board_indices();

            std::cout << "Remaining peg count: " << board->count_filled() << std::endl;

            if (board->count_filled() == 1) {
                std::cout << "Congrats! You are a genius!" << std::endl;
                break;
            }

            int from, over, to;
            std::cout << "Enter three indexes FROM/OVER/TO: ";
            std::cin >> from;
            if (from == -1) {
                std::cout << "Exiting the game..." << std::endl;
                break;
            }
            std::cin >> over >> to;

            if (from < 0 || from >= TOTAL_NODES || over < 0 || over >= TOTAL_NODES || to < 0 || to >= TOTAL_NODES) {
                std::cout << "Index error!" << std::endl;
                continue;
            }

            if (!board->try_move(from, over, to)) {
                std::cout << "Invalid move." << std::endl;
            }
        }
        delete board;
        return 0;
    }
    delete board;
    return 1;
}