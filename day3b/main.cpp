#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> getInput(std::string filename){
    std::vector<std::string> output;
    std::fstream f(filename);
    std::string line;
    while(getline(f, line)){
        output.push_back(line);
    }
    
    f.close();
    return output;
}

std::string checkIntForward(int i, int j, std::vector<std::string>& input){
    std::string num = "";
    while(j < input[i].size() && isdigit(input[i][j])){
        num.push_back(input[i][j]);
        j++;
    }
    return num;
}

std::string checkIntBackward(int i, int j, std::vector<std::string>& input){
    std::string num;
    while(j >= 0 && isdigit(input[i][j])){
        num.push_back(input[i][j]);
        j--;
    }

    std::reverse(num.begin(), num.end());
    return num;
}

int main(){
    int sum = 0;
    std::vector<std::string> input = getInput("input.txt");
    
    for(int i = 0; i < input.size(); i++){
        std::size_t pos = input[i].find_first_of("*");
        while(pos != std::string::npos){
            std::vector<std::string> nums;
            for(int o = -1; o <= 1; o++){
                std::string numf = "";
                std::string numr = "";
                numf = checkIntForward(i+o, pos+1, input);
                numr = checkIntBackward(i+o, pos-1, input);
                if(isdigit(input[i+o][pos])){
                    numr.push_back(input[i+o][pos]);
                    nums.push_back(numr + numf);
                }
                else{
                    if(numf != "") nums.push_back(numf);
                    if(numr != "") nums.push_back(numr);
                }
            }

            if(nums.size() == 2) sum += stoi(nums[0]) * stoi(nums[1]);

            pos = input[i].find_first_of("*", pos+1);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}