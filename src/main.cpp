#include "Application.h"
#include "Menus.h"
int main()
{
    Application app;
    app.start();
    Menu menu = Menu(app);
    menu.mainMenu();
    return 0;
}