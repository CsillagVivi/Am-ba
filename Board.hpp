#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <functional>
#include "graphics.hpp"

class Board {
private:
    int x, y;
    int width, height;
    int rows, cols;
    std::vector<std::vector<char>> board;
    std::function<void(int, int)> on_click;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> winning_lines;

public:
    Board(int x, int y, int width, int height, int rows, int cols, std::function<void(int, int)> on_click);

    void draw(genv::canvas &canvas) const;
    void handle_event(const genv::event &ev);
    void set_on_click(std::function<void(int, int)> on_click);

    void set_cell(int row, int col, char player);
    char get_cell(int row, int col) const;
    bool is_full() const;
    bool is_inside(int px, int py) const;

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    void add_winning_line(std::pair<int, int> start, std::pair<int, int> end);
};

#endif // BOARD_HPP
