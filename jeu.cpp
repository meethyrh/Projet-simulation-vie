#include <iostream>
#include <vector>
#include "anipop.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


using namespace std;

int main(){
    
    
    Population p;
    for(int i = 0;i<10;i++){
        Animal a = {Espece::Lapin, {1,0}, p.reserve()};
        p.set(a);
    }
    cout<<p;
    
//     cout << a.toString() << endl;
//     array<int, 6> n;
//     for(int i = 0;i<6;i++)cout<<n[i];
    
    
    return 0;
}