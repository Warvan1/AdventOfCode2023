#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    std::vector<std::string> numStr = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;
    while(getline(f, line)){
        int first = -1;
        int last = -1;
        for (int i = 0; i < line.size(); i++){
            if(isdigit(line[i])){
                if(first == -1){
                    first = line[i] - 48;
                }
                last = line[i] - 48;
            }
            else{
                for(auto ns : numStr){

                }
            }
        }
        sum += first*10 + last;
        std::cout << first*10 + last << " " << sum << " " << line << std::endl;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}