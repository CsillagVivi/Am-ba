#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include <functional>
#include <vector>
#include <string>

class Widget {
protected:
    int x, y, width, height;
public:
    Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    virtual void draw(genv::canvas &canvas) = 0;
    virtual void handle_event(const genv::event &ev) = 0;
};

class Button : public Widget {
    std::string label;
    std::function<void()> on_click;
public:
    Button(int x, int y, int width, int height, const std::string& label, std::function<void()> on_click);

    void draw(genv::canvas &canvas) override;
    void handle_event(const genv::event &ev) override;
};

class GameBoard : public Widget {
    int rows, cols;
    std::vector<std::vector<char>> board;
    std::function<void(int, int)> on_click;
public:
    GameBoard(int x, int y, int width, int height, int rows, int cols, std::function<void(int, int)> on_click);

    void draw(genv::canvas &canvas) override;
    void handle_event(const genv::event &ev) override;

    void set_cell(int row, int col, char player);
    char get_cell(int row, int col) const;
    bool is_full() const;
    bool is_inside(int px, int py) const;

    void set_on_click(std::function<void(int, int)> on_click);
};

#endif // WIDGET_HPP
