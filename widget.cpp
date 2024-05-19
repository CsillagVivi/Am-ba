#include "widget.hpp"

Button::Button(int x, int y, int width, int height, const std::string& label, std::function<void()> on_click)
    : Widget(x, y, width, height), label(label), on_click(on_click) {}

void Button::draw(genv::canvas &canvas) {
    canvas << genv::move_to(x, y) << genv::color(200, 200, 200) << genv::box(width, height);
    canvas << genv::move_to(x + 10, y + height / 2) << genv::color(0, 0, 0) << genv::text(label);
}

void Button::handle_event(const genv::event &ev) {
    if (ev.type == genv::ev_mouse && ev.button == genv::btn_left) {
        if (ev.pos_x > x && ev.pos_x < x + width && ev.pos_y > y && ev.pos_y < y + height) {
            on_click();
        }
    }
}

GameBoard::GameBoard(int x, int y, int width, int height, int rows, int cols, std::function<void(int, int)> on_click)
    : Widget(x, y, width, height), rows(rows), cols(cols), on_click(on_click) {
    board.resize(rows, std::vector<char>(cols, ' '));
}

void GameBoard::draw(genv::canvas &canvas) {

    int cell_width = width / cols;
    int cell_height = height / rows;


    for (int i = 0; i <= cols; ++i) {
        canvas << genv::move_to(x + i * cell_width, y) << genv::line(0, height);
    }
    for (int i = 0; i <= rows; ++i) {
        canvas << genv::move_to(x, y + i * cell_height) << genv::line(width, 0);
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == 'X') {
                canvas << genv::move_to(x + j * cell_width + cell_width / 2, y + i * cell_height + cell_height / 2) << genv::color(255, 0, 0) << genv::text("X");
            } else if (board[i][j] == 'O') {
                canvas << genv::move_to(x + j * cell_width + cell_width / 2, y + i * cell_height + cell_height / 2) << genv::color(0, 0, 255) << genv::text("O");
            }
        }
    }
}

void GameBoard::handle_event(const genv::event &ev) {
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

void GameBoard::set_on_click(std::function<void(int, int)> on_click) {
    this->on_click = on_click;
}

void GameBoard::set_cell(int row, int col, char player) {
    board[row][col] = player;
}

char GameBoard::get_cell(int row, int col) const {
    return board[row][col];
}

bool GameBoard::is_full() const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::is_inside(int px, int py) const {
    return px >= x && px < x + width && py >= y && py < y + height;
}
