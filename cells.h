#include "libs_and_tegs.h"

enum Status
{
    CLOSE,
    MARK,
    OPEN
};

class Cell
{
protected:
    Status status;

public:
    Cell()
    {
        status = CLOSE;
    }

    virtual ~Cell() {}

    Status get_status() { return status; }
    void set_status(Status new_status) { status = new_status; }

    virtual void openCell()
    {
        if (status == OPEN)
        {
            throw runtime_error("This cell is already open.");
        }
        else if (status == MARK)
        {
            throw runtime_error("This cell is marked! Unmark the cell before open it.");
        }
        else
        {
            status = OPEN;
        }
    }

    void markCreate()
    {
        if (status == OPEN)
        {
            throw runtime_error("Cell isn't close!");
        }
        else if (status == MARK)
        {

            throw runtime_error("This cell is already marked.");
        }
        else
        {
            status = MARK;
        }
    }

    void markDelete()
    {
        if (status == MARK)
        {
            status = CLOSE;
        }
        else
        {
            throw runtime_error("Cell isn't mark!");
        }
    }

    virtual void printCell() = 0;
};

class EmptyCell : public Cell
{
public:
    EmptyCell() : Cell() {}

    ~EmptyCell(){};

    void printCell()
    {
        switch (status)
        {
        case (OPEN):
            cout << "|___|";
            break;
        case (MARK):
            cout << "|_" << OPEN_FLAG << "F" << CLOSE_ALL << "_|";
            break;
        case (CLOSE):
            cout << "|_X_|";
            break;
        };
    }
};

class CountCell : public Cell
{
protected:
    int bomb_count;

public:
    CountCell() : Cell()
    {
        bomb_count = 0;
    }
    ~CountCell() {}

    void plusBomb()
    {
        bomb_count++;
    }

    void printCell()
    {
        switch (status)
        {
        case (OPEN):
            switch (bomb_count)
            {
            case 1:
                cout << "|_" << OPEN_1 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 2:
                cout << "|_" << OPEN_2 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 3:
                cout << "|_" << OPEN_3 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 4:
                cout << "|_" << OPEN_4 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 5:
                cout << "|_" << OPEN_5 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 6:
                cout << "|_" << OPEN_6 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 7:
                cout << "|_" << OPEN_7 << bomb_count << CLOSE_ALL << "_|";
                break;
            case 8:
                cout << "|_" << OPEN_8 << bomb_count << CLOSE_ALL << "_|";
                break;
            default:
                cout << "|_" << bomb_count << "_|";
                break;
            };
            break;
        case (MARK):
            cout << "|_" << OPEN_FLAG << "F" << CLOSE_ALL << "_|";
            break;
        case (CLOSE):
            cout << "|_X_|";
            break;
        };
    }
};

class BombCell : public Cell
{
public:
    BombCell() : Cell() {}

    ~BombCell(){};

    void openCell()
    {
        if (status == MARK)
        {
            throw runtime_error("This cell is marked! Unmark the cell before open it.");
        }
        else
        {
            status = OPEN;
            throw runtime_error("You are explode!!!");
        }
    }

    void printCell()
    {
        switch (status)
        {
        case (OPEN):
            cout << "|_" << OPEN_BOMB << "B" << CLOSE_ALL << "_|";
            break;
        case (MARK):
            cout << "|_" << OPEN_FLAG << "F" << CLOSE_ALL << "_|";
            break;
        case (CLOSE):
            cout << "|_X_|";
            break;
        };
    }
};