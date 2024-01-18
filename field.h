#include "cells.h"

class Field
{
protected:
    int rows;
    int columns;
    int mines;
    Cell ***field;

public:
    Field()
    {
        rows = 9;
        columns = 9;
        mines = 10;
        field = new Cell **[rows];
        for (int i = 0; i < rows; ++i)
        {
            field[i] = new Cell *[columns];
            for (int j = 0; j < columns; ++j)
            {
                field[i][j] = new EmptyCell();
            }
        }
        bombSpawn();
        countSpawn();
        countCount();
    }

    Field(int difficult)
    {
        switch (difficult)
        {
        case 1:

            rows = 9;
            columns = 9;
            mines = 10;
            break;
        case 2:

            rows = 16;
            columns = 16;
            mines = 40;
            break;
        case 3:

            rows = 16;
            columns = 30;
            mines = 99;
            break;
        default:
            rows = 9;
            columns = 9;
            mines = 10;
            break;
        };
        field = new Cell **[rows];
        for (int i = 0; i < rows; ++i)
        {
            field[i] = new Cell *[columns];
            for (int j = 0; j < columns; ++j)
            {
                field[i][j] = new EmptyCell();
            }
        }
        bombSpawn();
        countSpawn();
        countCount();
    }

    Field(int _rows, int _columns, int _mines) : rows(_rows), columns(_columns), mines(_mines), field(new Cell **[rows])
    {
        for (int i = 0; i < rows; ++i)
        {
            field[i] = new Cell *[columns];
            for (int j = 0; j < columns; ++j)
            {
                field[i][j] = new EmptyCell();
            }
        }
        bombSpawn();
        countSpawn();
        countCount();
    }

    ~Field()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                delete field[i][j];
            }
            delete[] field[i];
        }
        delete[] field;
    }

    bool isCellCheck(int i, int j)
    {
        if ((i >= 0) && (i < rows) && (j >= 0) && (j < columns))
        {
            return true;
        }
        return false;
    }

    void openCell(int i, int j)
    {
        if (!isCellCheck(i - 1, j - 1) || field[i - 1][j - 1]->get_status() == OPEN)
        {
            return;
        }

        field[i - 1][j - 1]->openCell();

        if (typeid(*field[i - 1][j - 1]) == typeid(EmptyCell))
        {
            for (int x = -1; x <= 1; ++x)
            {
                for (int y = -1; y <= 1; ++y)
                {
                    openCell(i + x, j + y);
                }
            }
        }
    }

    void markCreate(int i, int j)
    {
        field[i - 1][j - 1]->markCreate();
    }

    void markDelete(int i, int j)
    {
        field[i - 1][j - 1]->markDelete();
    }

    void printField()
    {
        cout << "\033[H\033[J";
        int count = 1;
        cout << "\t";
        for (int i = 0; i < columns; i++)
        {
            if (i < 9)
            {
                cout << "  " << i + 1 << "  ";
            }
            else
            {
                cout << " " << i + 1 << "  ";
            }
        }
        cout << endl;

        cout << "\t";
        for (int j = 0; j < columns; j++)
        {
            cout << " ___ ";
        }
        cout << endl;

        for (int i = 0; i < rows * 2; i++)
        {
            if (i % 2 == 0)
            {
                cout << count << "\t";
                for (int j = 0; j < columns; j++)
                {
                    field[count - 1][j]->printCell();
                }
                cout << endl;
                count++;
            }
            else
            {
                if (count < rows + 1)
                {
                    cout << "\t";
                    for (int j = 0; j < columns; j++)
                    {
                        cout << " ___ ";
                    }
                    cout << endl;
                }
            }
        }
        cout << endl;
    }

    void updateCell(int i, int j, Cell *newCell)
    {
        delete field[i][j];
        field[i][j] = newCell;
    }

private:
    void bombSpawn()
    {
        int i = 0;
        int j = 0;
        for (int bomb = 0; bomb < mines; bomb++)
        {
            i = rand() % rows;
            j = rand() % columns;
            if (typeid(*field[i][j]) == typeid(BombCell))
            {
                bomb--;
            }
            else
            {
                updateCell(i, j, new BombCell());
            }
        }
    }

    void countSpawn()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (typeid(*field[i][j]) == typeid(BombCell))
                {
                    if (i != 0)
                    {
                        if (j != 0)
                        {
                            if (typeid(*field[i - 1][j - 1]) == typeid(EmptyCell))
                            {
                                updateCell(i - 1, j - 1, new CountCell());
                            }
                        }
                        if (typeid(*field[i - 1][j]) == typeid(EmptyCell))
                        {
                            updateCell(i - 1, j, new CountCell());
                        }
                        if (j != columns - 1)
                        {
                            if (typeid(*field[i - 1][j + 1]) == typeid(EmptyCell))
                            {
                                updateCell(i - 1, j + 1, new CountCell());
                            }
                        }
                    }
                    if (j != 0)
                    {
                        if (typeid(*field[i][j - 1]) == typeid(EmptyCell))
                        {
                            updateCell(i, j - 1, new CountCell());
                        }
                    }
                    if (j != columns - 1)
                    {
                        if (typeid(*field[i][j + 1]) == typeid(EmptyCell))
                        {
                            updateCell(i, j + 1, new CountCell());
                        }
                    }
                    if (i != rows - 1)
                    {
                        if (j != 0)
                        {
                            if (typeid(*field[i + 1][j - 1]) == typeid(EmptyCell))
                            {
                                updateCell(i + 1, j - 1, new CountCell());
                            }
                        }
                        if (typeid(*field[i + 1][j]) == typeid(EmptyCell))
                        {
                            updateCell(i + 1, j, new CountCell());
                        }
                        if (j != columns - 1)
                        {
                            if (typeid(*field[i + 1][j + 1]) == typeid(EmptyCell))
                            {
                                updateCell(i + 1, j + 1, new CountCell());
                            }
                        }
                    }
                }
            }
        }
    }

    void countCount()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (typeid(*field[i][j]) == typeid(CountCell))
                {
                    if (i != 0)
                    {
                        if (j != 0)
                        {
                            if (typeid(*field[i - 1][j - 1]) == typeid(BombCell))
                            {
                                dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                            }
                        }
                        if (typeid(*field[i - 1][j]) == typeid(BombCell))
                        {
                            dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                        }
                        if (j != columns - 1)
                        {
                            if (typeid(*field[i - 1][j + 1]) == typeid(BombCell))
                            {
                                dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                            }
                        }
                    }
                    if (j != 0)
                    {
                        if (typeid(*field[i][j - 1]) == typeid(BombCell))
                        {
                            dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                        }
                    }
                    if (j != columns - 1)
                    {
                        if (typeid(*field[i][j + 1]) == typeid(BombCell))
                        {
                            dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                        }
                    }
                    if (i != rows - 1)
                    {
                        if (j != 0)
                        {
                            if (typeid(*field[i + 1][j - 1]) == typeid(BombCell))
                            {
                                dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                            }
                        }
                        if (typeid(*field[i + 1][j]) == typeid(BombCell))
                        {
                            dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                        }
                        if (j != columns - 1)
                        {
                            if (typeid(*field[i + 1][j + 1]) == typeid(BombCell))
                            {
                                dynamic_cast<CountCell *>(field[i][j])->plusBomb();
                            }
                        }
                    }
                }
            }
        }
    }
};