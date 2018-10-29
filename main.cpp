#include "header.hpp"
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Error. Please enter: a.out filename.xml" <<endl;
        return EXIT_FAILURE;
    }
    //Start game
    findAllStuff(argv);
    gameStart();

    return EXIT_SUCCESS;
}