#include "app.h"
#include <windows.h>

int main() {

    SetConsoleCP(1251);           
    SetConsoleOutputCP(1251);     

    App app;
    app.run();
    return 0;
}
