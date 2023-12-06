#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main(){
    std::fstream f("input.txt");
    std::string line;
    std::vector<std::vector<int>> races;
    int ri = 0;
    while(getline(f, line)){
        races.push_back({});
        std::string num = "";
        for(char c : line){
            if(isdigit(c)){
                num += c;
            }
            else if (c == ' ' && num.size() != 0){
                races[ri].push_back(stoi(num));
                num = "";
            }
        }
        if(num.size() != 0){
            races[ri].push_back(stoi(num));
        }
        ri++;
    }

    std::vector<int> results;
    for(int i = 0; i < races[0].size(); i++){
        int result = 0;
        for(int j = 1; j < races[0][i]; j++){
            int res = (races[0][i] - j)*j;
            if(res > races[1][i]){
                result++;
            }
        }
        results.push_back(result);
    }

    int result = 1;
    for(int r : results){
        result = result*r;
    }
    std::cout << result << std::endl;

    f.close();
    return 0;
}