#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(NULL));

    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2019" << endl;
    cout << "Programming Assignment 3" << endl;
    cout << "                                  ,'\\" << endl;
    cout << "     _.----.       ____         ,'  _\\   ___    ___     ____" << endl;
    cout << " _,-'       `.    |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`." << endl;
    cout << " \\     __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |" << endl;
    cout << "  \\    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |" << endl;
    cout << "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |" << endl;
    cout << "    \\     ,-'/  / \\  \\   ,'   | \\/ / ,`.|         /  / \\ \\  |     |" << endl;
    cout << "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |" << endl;
    cout << "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |" << endl;
    cout << "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |" << endl;
    cout << "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |" << endl;

    Model Model1;
    View view = View();
    Model1.ShowStatus();
    Model1.Display(view);
    view.clear();
    Point2D Loc;
    int ID1, ID2;
    int i = 1;
    unsigned int stamina_amount, unit_amount;
    char UserInput = ' ';
    while (true)
    {
        cout << "Enter command: ";
        cin >> UserInput;
        switch (UserInput) {
            case 'm':
                cin >> ID1 >> Loc.x >> Loc.y;
                GameCommand().DoMoveCommand(Model1, ID1, Loc);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 'g':
                cin >> ID1 >> ID2;
                GameCommand().DoMoveToGymCommand(Model1, ID1, ID2);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 'c':
                cin >> ID1 >> ID2;
                GameCommand().DoMoveToCenterCommand(Model1, ID1, ID2);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 's':
                cin >> ID1;
                GameCommand().DoStopCommand(Model1, ID1);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 'r':
                cin >> ID1 >> stamina_amount;
                GameCommand().DoRecoverInCenterCommand(Model1, ID1, stamina_amount);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 't':
                cin >> ID1 >> unit_amount;
                GameCommand().DoTrainInGymCommand(Model1, ID1, unit_amount);
                Model1.ShowStatus();
                Model1.Display(view);
                break;
            case 'v':
                GameCommand().DoGoCommand(Model1, view);
                break;
            case 'x':
                GameCommand().DoRunCommand(Model1, view);
                break;
            case 'q':
                cout << "Program terminated" << endl;
                return 0;
            default:
            {
                cout << "Please try again: ";
                break;
            }


        }
    }
    return 0;
}