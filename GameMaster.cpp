#include "GameMaster.hpp"


GameMaster::GameMaster(Board* board)
    : board(board), current_player('X'), winning_line_start(-1, -1), winning_line_end(-1, -1) {}

void GameMaster::handle_click(int row, int col) {
    if (board->get_cell(row, col) == ' ' && !is_game_over()) {
        board->set_cell(row, col, current_player);
        if (check_winner(row, col)) {
            board->add_winning_line(winning_line_start, winning_line_end);
        } else if (board->is_full()) {

        } else {
            switch_player();
        }
    }
}

bool GameMaster::check_winner(int row, int col) {
    static const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {0, 1}, {1, 1}, {1, -1}
    };

    for (const auto& dir : directions) {
        if (check_direction(row, col, dir.first, dir.second)) {
            return true;
        }
    }

    return false;
}

bool GameMaster::check_direction(int row, int col, int d_row, int d_col) {
    int count = 1;
    int start_row = row, start_col = col, end_row = row, end_col = col;

    for (int i = 1; i < 5; ++i) {
        int new_row = row + i * d_row;
        int new_col = col + i * d_col;
        if (new_row >= 0 && new_row < board->get_rows() &&
            new_col >= 0 && new_col < board->get_cols() &&
            board->get_cell(new_row, new_col) == current_player) {
            count++;
            end_row = new_row;
            end_col = new_col;
        } else {
            break;
        }
    }

    for (int i = 1; i < 5; ++i) {
        int new_row = row - i * d_row;
        int new_col = col - i * d_col;
        if (new_row >= 0 && new_row < board->get_rows() &&
            new_col >= 0 && new_col < board->get_cols() &&
            board->get_cell(new_row, new_col) == current_player) {
            count++;
            start_row = new_row;
            start_col = new_col;
        } else {
            break;
        }
    }

    if (count >= 5) {
        set_winning_line(start_row, start_col, end_row, end_col);
        return true;
    }

    return false;
}

void GameMaster::set_winning_line(int start_row, int start_col, int end_row, int end_col) {
    winning_line_start = {start_row, start_col};
    winning_line_end = {end_row, end_col};
}

void GameMaster::switch_player() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

bool GameMaster::is_game_over() const {
    return has_winner() || board->is_full();
}

bool GameMaster::has_winner() const {
    return winning_line_start.first != -1;
}

std::pair<int, int> GameMaster::get_winning_line_start() const {
    return winning_line_start;
}

std::pair<int, int> GameMaster::get_winning_line_end() const {
    return winning_line_end;
}
