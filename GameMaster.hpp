#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "Board.hpp"

class GameMaster {
    Board* board;
    char current_player;
    std::pair<int, int> winning_line_start;
    std::pair<int, int> winning_line_end;

public:
    GameMaster(Board* board);
    void handle_click(int row, int col);
    bool check_winner(int row, int col);

    bool is_game_over() const;
    bool has_winner() const;
    std::pair<int, int> get_winning_line_start() const;
    std::pair<int, int> get_winning_line_end() const;

private:
    void switch_player();
    bool check_direction(int row, int col, int d_row, int d_col);
    void set_winning_line(int start_row, int start_col, int end_row, int end_col);
};

#endif // GAMEMASTER_HPP
