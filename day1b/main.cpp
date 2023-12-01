#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int calcStr(std::string& line, int i, std::vector<std::string>& numStr){
    int output = -1;
    if(isdigit(line[i])){
        output = line[i] - 48;
    }
    else{
        for(int j = 0; j < numStr.size(); j++){
            if(line.substr(i, numStr[j].size()) == numStr[j]){
                output = j;
                break;
            }
        }
    }
    return output;
}

int main(){
    std::vector<std::string> numStr = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;
    while(getline(f, line)){
        int first = -1;
        int last = -1;
        for (int i = 0; i < line.size(); i++){
            first = calcStr(line, i, numStr);
            if(first != -1){
                break;
            }
        }
        for (int i = line.size()-1; i >= 0; i--){
            last = calcStr(line, i, numStr);
            if(last != -1){
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