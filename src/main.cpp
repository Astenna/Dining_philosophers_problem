#include <iostream>
#include "../inc/table.h"

int main() {

    // should be from args
    int philosopherNumber = 3;
    char entered = 'a';

    std::cout << "Enter q to stop theards!" << std::endl;
    table mainTable = table(philosopherNumber);
    while(entered != 'q') {
        std::cout << "Enter q to stop theards!" << std::endl;
        std::cin >> entered;
        std::cout << "exited";
    }
    mainTable.stop();
}