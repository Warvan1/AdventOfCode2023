#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<std::string> split(std::string str, char del){
    std::vector<std::string> output;
    std::stringstream ss(str);
    std::string token;
    while(!ss.eof()){
        getline(ss, token, del);
        output.push_back(token);
    }
    return output;
}

bool notAllZero(std::vector<int> nums){
    for(int n: nums){
        if(n != 0){
            return true;
        }
    }
    return false;
}

int main(){
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;

    while(getline(f, line)){
        std::vector<std::string> input = split(line, ' ');
        std::vector<int> nums;
        for(std::string s: input){
            nums.push_back(stoi(s));
        }
        int startNum = nums[0];

        std::vector<std::vector<int>> differences;
        while(notAllZero(nums)){
            std::vector<int> diff;
            for(int i = 0; i < nums.size()-1; i++){
                diff.push_back(nums[i+1]-nums[i]);
            }
            differences.push_back(diff);
            nums = diff;
        }

        int nextValue = 0;
        for(int i = differences.size()-2; i >= 0; i--){
            nextValue = differences[i][0] - nextValue;
        }
        nextValue = startNum - nextValue;

        sum += nextValue;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}