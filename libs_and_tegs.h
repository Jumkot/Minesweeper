#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sys/time.h>
#include <time.h>

#define OPEN_FLAG "\033[1;3;31m"
#define OPEN_BOMB "\033[6;31m"

#define OPEN_1 "\033[34m"   // голубой
#define OPEN_2 "\033[32m"   // зелёный
#define OPEN_3 "\033[31m"   // красный
#define OPEN_4 "\033[35m"   // розовый
#define OPEN_5 "\033[33m"   // жёлтый
#define OPEN_6 "\033[36m"   // бирюзовый
#define OPEN_7 "\033[2;37m" // серый
#define OPEN_8 "\033[2;35m" // фиолетовый

#define CLOSE_ALL "\033[0m"

using namespace std;