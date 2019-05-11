#include <iostream>
#include "../inc/table.h"
#include <string>

int main(int argc, char *argv[]) {

    int philosopherNumber = 3;
    int entered = 'a';

    if( argc > 1) {
        try {
            philosopherNumber = std::stoi(argv[1]);
        }
        catch(std::invalid_argument &obj) {
            std::cout<<"Not a integer number given. Philosopher number set to default (=3)." 
                        << std::endl;
        }
    }
    
    table mainTable = table(philosopherNumber);

    while(entered != 'q' && std::cin) {
        std::cin >> entered;
    }
    mainTable.stop();
}