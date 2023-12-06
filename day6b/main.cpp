#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

bool win_num(long long wait, long long total, long long target){
    long long res = (total - wait) * wait;
    return res > target;
}

long long find_min(long long pMin, long long pMax, long long& total, long long& target){
    //Base Case
    if(pMax - pMin < 4){
        for(long long i = pMin; pMin <= pMax; pMin++){
            std::cout << pMin << std::endl;
            if(win_num(pMin, total, target)){
                return pMin;
            }
        }
        return -1;
    }
    long long middle = pMin + (pMax - pMin)/2;
    std::cout << middle << std::endl;
    //step case
    if(win_num(middle, total, target)){
        return find_min(pMin, middle, total, target);
    }
    else{
        return find_min(middle, pMax, total, target);
    }
}

long long find_max(long long pMin, long long pMax, long long& total, long long& target){
    //Base Case
    if(pMax - pMin < 4){
        for(long long i = pMax; pMin <= pMax; pMax--){
            std::cout << pMax << std::endl;
            if(win_num(pMax, total, target)){
                return pMax;
            }
        }
        return -1;
    }
    long long middle = pMin + (pMax - pMin)/2;
    std::cout << middle << std::endl;
    //step case
    if(win_num(middle, total, target)){
        return find_max(middle, pMax, total, target);
    }
    else{
        return find_max(pMin, middle, total, target);
    }
}

int main(){
    std::fstream f("input.txt");
    std::string line;
    std::vector<long long> race;
    int ri = 0;
    while(getline(f, line)){
        std::string num = "";
        for(char c : line){
            if(isdigit(c)){
                num += c;
            }
        }
        race.push_back(stoll(num));
        ri++;
    }

    std::cout << race[0] << " " << race[1] << std::endl;
    long long minWin = find_min(1, race[0] - 1, race[0], race[1]);
    std::cout << "--------------" << std::endl;
    long long maxWin = find_max(1, race[0] - 1, race[0], race[1]);

    std::cout << minWin << " *" << std::endl;
    std::cout << maxWin << " *" << std::endl;

    std::cout << maxWin - minWin + 1 << " **" << std::endl;
    f.close();
    return 0;
}