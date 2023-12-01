#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;
    while(getline(f, line)){
        int first = -1;
        int last = -1;
        for (char c : line){
            if(isdigit(c)){
                if(first == -1){
                    first = c;
                }
                last = c;
            }
        }
        first -= 48;
        last -= 48;
        sum += first*10 + last;
        // std::cout << first*10 + last << " " << sum << " " << line << std::endl;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}