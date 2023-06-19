#include "Utaxi.hpp"
using namespace std;

int main(int argv, char *argc[]){
    Utaxi utaxi;
    utaxi.read_info(argc[1]);
    utaxi.start();
}
