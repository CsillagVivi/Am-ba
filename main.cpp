#include "graphics.hpp"
#include "Board.hpp"
#include "GameMaster.hpp"

int main() {
    genv::gout.open(600, 600);

    Board board(50, 50, 500, 500, 15, 15, nullptr);
    GameMaster game_master(&board);

    board.set_on_click([&game_master](int row, int col) {
        game_master.handle_click(row, col);
    });

    genv::event ev;
    while (genv::gin >> ev) {
        board.handle_event(ev);

        genv::gout << genv::move_to(0, 0) << genv::color(255, 255, 255) << genv::box(600, 600);
        board.draw(genv::gout);
        genv::gout << genv::refresh;
    }

    return 0;
}
