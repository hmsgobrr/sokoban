#include "Program.h"

int main() {
    Program prog;
    
    if (prog.init(800, 600, "titol") == -1) {
        return -1;
    }

    prog.bg(Warna(0, 0, 0, 255));
    while (!prog.wsc()) {
        prog.tick();
    }
    prog.shut();
}
