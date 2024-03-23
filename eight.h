#include <iostream>
#include <fstream>
using namespace std;

#define SOL3

void output(int situation, ofstream &fout){
    string str = "\n";
    for(int i = 0; i < 9; i++){
        int num = situation%10;
        situation /= 10;
        if(num != 0)
            str = to_string(num) + " " + str;
        else
            str = "  " + str;
        if(i == 2 || i == 5)
            str = "\n" + str;
    }
    fout<<str<<endl;
}

bool isTarget(int situation){
    return situation == 12345678;
}

int h(int situation){
    int h = 0;
    for(int i = 8; i >= 0; i--){
        int num = situation%10;

        #ifdef SOL1
        h += abs(num - i);

        #elif defined SOL2
        int row = i/3;
        int col = i%3;
        int row0 = num/3;
        int col0 = num%3;
        h += abs(row - row0) + abs(col - col0);

        #else
        if(num != i)
            h++;
        #endif
        
        situation /= 10;
    }
    return h;
}

int posZero(int situation){
    for(int i = 8; i >= 0; i--){
        if(situation % 10 == 0)
            return i;
        situation /= 10;
    }
    return -1;
}

int swap(int situation, int pos1, int pos2){
    int num[9];
    for(int i = 8; i >= 0; i--){
        num[i] = situation%10;
        situation /= 10;
    }
    std::swap(num[pos1], num[pos2]);
    int newSituation = 0;
    for(int i = 0; i < 9; i++)
        newSituation = newSituation*10 + num[i];
    return newSituation;
}