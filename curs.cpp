#include "field.h"

class Game : public Field
{
protected:
    int difficult;
    int time;

public:
    Game(int select_dif) : Field(select_dif), difficult(select_dif), time(wtime()) {}
    Game(int rows, int columns, int mines) : Field(rows, columns, mines), difficult(4), time(wtime()) {}

    double get_time() { return time; }
    void set_time(double _time) { time = _time; }

    bool processGame()
    {
        int x = 0;
        int y = 0;
        cout << "Enter the coordinates of the cell to interact with:" << endl;
        enterCoordinates(&x, &y);

        cout << "Select action (enter number):" << endl;
        int choice = selectOptions();

        switch (choice)
        {
        case 1:
            try
            {
                openCell(x, y);
                printField();
            }
            catch (const exception &e)
            {
                string str_e = e.what();
                if (str_e == "You are explode!!!")
                {
                    endGame(e);
                }
                else
                {
                    printField();
                    cerr << e.what() << endl;
                }
            }
            if (isWin())
            {
                endGame();
            }
            break;
        case 2:
            try
            {
                markCreate(x, y);
                printField();
            }
            catch (const exception &e)
            {
                printField();
                cerr << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                markDelete(x, y);
                printField();
            }
            catch (const exception &e)
            {
                printField();
                cerr << e.what() << endl;
            }
            break;
        case 4:
            processGame();
            break;
        case 5:
            return false;
        };
        return true;
    }

    int selectOptions()
    {
        int choice = 0;
        cout << "\t1. Open cell" << endl
             << "\t2. Mark cell" << endl
             << "\t3. Unmark cell" << endl
             << "\t4. Cancel cell selection" << endl
             << "\t5. Finish the game" << endl;
        cin >> choice;
        if ((choice < 1) || (choice > 5))
        {
            cout << "\033[H\033[J";
            cout << "Select correct option number" << endl;
            choice = selectOptions();
        }
        return choice;
    }

    void enterCoordinates(int *x, int *y)
    {
        *x = 0;
        *y = 0;
        cin >> *x >> *y;
        if (!(*x > 0) || !(*x <= rows) || !(*y > 0) || !(*y <= columns))
        {
            cout << "\033[H\033[J";
            cout << "Enter the correct coordinates: " << endl;
            enterCoordinates(x, y);
        }
    }

    bool isWin()
    {
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < columns; ++y)
            {
                if ((typeid(*field[x][y]) != typeid(BombCell)) && (field[x][y]->get_status() != OPEN))
                {
                    return false;
                }
            }
        }
        return true;
    }

    void endGame(const exception &e)
    {
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < columns; ++y)
            {
                if (typeid(*field[x][y]) == typeid(BombCell))
                {
                    field[x][y]->set_status(OPEN);
                }
            }
        }
        printField();
        cerr << e.what() << endl;
        time = wtime() - time;
        showTime();
        exit(EXIT_SUCCESS);
    }

    void endGame()
    {
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < columns; ++y)
            {
                if (typeid(*field[x][y]) == typeid(BombCell))
                {
                    field[x][y]->set_status(OPEN);
                }
            }
        }
        printField();
        cout << "YOU'RE WIN!!!" << endl;
        time = wtime() - time;
        showTime();
        exit(EXIT_SUCCESS);
    }

    int wtime()
    {
        struct timeval t;
        gettimeofday(&t, NULL);
        return (int)t.tv_sec + (int)t.tv_usec * 1E-6;
    }

    void showTime()
    {
        int min = time / 60;
        int sec = time - min * 60;
        cout << "Time your game: " << min << " minutes and " << sec << " seconds" << endl;
    }
};

class Minesweeper
{
public:
    Minesweeper() {}
    ~Minesweeper() {}

    void menu()
    {
        int choice = 0;
        cout << "\033[H\033[J";
        cout << "\t\t\t\tMINESWEEPER" << endl
             << " 1) New game" << endl
             << " 2) Exit\n"
             << endl
             << "Select your option number" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
            newGame();
            break;
        case 2:
            exitGame();
            break;
        default:
            cout << "Select correct option number" << endl;
            menu();
            break;
        };
    }
    void newGame()
    {
        cout << "\033[H\033[J";
        int choice = 0;
        cout << "Select your difficult:" << endl
             << " 1) EASY (9x9 field, 10 mines)" << endl
             << " 2) NORMAL (16x16 field, 40 mines)" << endl
             << " 3) HARD (16x30 field, 99 mines)" << endl
             << " 4) CUSTOM\n"
             << endl
             << "Select your option number" << endl;

        cin >> choice;
        if ((choice > 0) && (choice < 4))
        {
            Game game(choice);
            game.printField();
            while (game.processGame())
            {
            }
            exitGame(game);
        }
        else if (choice == 4)
        {
            int rows = 0;
            int columns = 0;
            int mines = 0;
            cout << "Enter the number of rows: ";
            cin >> rows;
            cout << "\nEnter the number of columns: ";
            cin >> columns;
            cout << "\nEnter the number of mines: ";
            cin >> mines;
            Game game(rows, columns, mines);
            game.printField();
            while (game.processGame())
            {
            }
            exitGame(game);
        }
        else
        {
            cout << "Select correct option number" << endl;
            newGame();
        }
    }

    void exitGame()
    {
        string sure;
        cout << "\033[H\033[J";
        cout << "Are you sure you want to finish the game?" << endl;
        cout << "YES\t\t\tNO" << endl;
        cin >> sure;
        if (sure == "YES")
        {
            cout << "You finished the game." << endl;
            exit(EXIT_SUCCESS);
        }
        else if (sure == "NO")
        {
            menu();
        }
        else
        {
            exitGame();
        }
    }

    void exitGame(Game &game)
    {
        string sure;
        cout << "\033[H\033[J";
        cout << "Do you want to finish the game?" << endl;
        cout << "YES\t\t\tNO" << endl;
        cin >> sure;
        if (sure == "YES")
        {
            game.set_time(game.wtime() - game.get_time());
            game.showTime();
            cout << "You finished the game." << endl;
            exit(EXIT_SUCCESS);
        }
        else if (sure == "NO")
        {
            game.printField();
            game.processGame();
        }
        else
        {
            exitGame(game);
        }
    }
};

int main()
{
    srand((time(nullptr)));

    Minesweeper minesweeper;

    minesweeper.menu();

    return 0;
}