#include "Board.hpp"

Board::Board(int x, int y, int width, int height, int rows, int cols, std::function<void(int, int)> on_click)
    : x(x), y(y), width(width), height(height), rows(rows), cols(cols), on_click(on_click) {
    board.resize(rows, std::vector<char>(cols, ' '));
}


void Board::draw(genv::canvas &canvas) const {
    int cell_width = width / cols;
    int cell_height = height / rows;

    canvas << genv::color(200, 200, 200);
    for (int i = 0; i <= cols; ++i) {
        canvas << genv::move_to(x + i * cell_width, y) << genv::line(0, height);
    }
    for (int i = 0; i <= rows; ++i) {
        canvas << genv::move_to(x, y + i * cell_height) << genv::line(width, 0);
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == 'X') {
                canvas << genv::color(255, 0, 0);
                canvas << genv::move_to(x + j * cell_width + cell_width / 2 - 5, y + i * cell_height + cell_height / 2 + 5);
                canvas << genv::text("X");
            } else if (board[i][j] == 'O') {
                canvas << genv::color(0, 0, 255);
                canvas << genv::move_to(x + j * cell_width + cell_width / 2 - 5, y + i * cell_height + cell_height / 2 + 5);
                canvas << genv::text("O");
            }
        }
    }


    for (const auto& line : winning_lines) {
        auto [start, end] = line;
        canvas << genv::color(0, 255, 0);
        canvas << genv::move_to(x + start.second * cell_width + cell_width / 2, y + start.first * cell_height + cell_height / 2);
        canvas << genv::line_to(x + end.second * cell_width + cell_width / 2, y + end.first * cell_height + cell_height / 2);
    }
}

void Board::handle_event(const genv::event &ev) {
    if (ev.type == genv::ev_mouse && ev.button == genv::btn_left) {
        int cell_width = width / cols;
        int cell_height = height / rows;
        int col = (ev.pos_x - x) / cell_width;
        int row = (ev.pos_y - y) / cell_height;
        if (row >= 0 && row < rows && col >= 0 && col < cols && board[row][col] == ' ') {
            if (on_click) {
                on_click(row, col);
            }
        }
    }
}

void Board::set_on_click(std::function<void(int, int)> on_click) {
    this->on_click = on_click;
}

void Board::set_cell(int row, int col, char player) {
    board[row][col] = player;
}

char Board::get_cell(int row, int col) const {
    return board[row][col];
}

bool Board::is_full() const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool Board::is_inside(int px, int py) const {
    return px >= x && px <= x + width && py >= y && py <= y + height;
}

void Board::add_winning_line(std::pair<int, int> start, std::pair<int, int> end) {
    winning_lines.emplace_back(start, end);
}
