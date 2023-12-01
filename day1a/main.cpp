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
        for (int i = 0; i < line.size(); i++){
            if(isdigit(line[i])){
                first = line[i] - 48;
                break;
            }
        }
        for(int i = line.size()-1; i >= 0; i--){
            if(isdigit(line[i])){
                last = line[i] - 48;
                break;
            }
        }
        sum += first*10 + last;
        std::cout << first << " " << last << " " << sum << " " << line << std::endl;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}