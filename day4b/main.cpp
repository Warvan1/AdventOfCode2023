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

void recurse_wins(int index, std::vector<int>& wins, int& sum){
    for(int i = 1; i <= wins[index]; i++){
        recurse_wins(index + i, wins, sum);
    }
    sum++;
}

int main(){
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;
    std::vector<int> wins;
    while(getline(f, line)){
        line = split(line, ':')[1];
        std::vector<std::string> input = split(line, ' ');
        std::vector<int> winning;
        std::vector<int> nums;
        bool pipe = false;

        for(int i = 0; i < input.size(); i++){
            if(input[i] != ""){
                if(input[i] == "|"){
                    pipe = true;
                }
                else{
                    if(!pipe){
                        winning.push_back(stoi(input[i]));
                    }
                    else{
                        nums.push_back(stoi(input[i]));
                    }
                }
            }
        }

        std::sort(winning.begin(), winning.end());
        std::sort(nums.begin(), nums.end());

        int i = 0;
        int j = 0;
        int count = 0;
        while(i < winning.size() && j < nums.size()){
            if(winning[i] == nums[j]){
                i++;
                j++;
                count++;
            }
            else if(winning[i] < nums[j]){
                i++;
            }
            else{
                j++;
            }
        }

        wins.push_back(count);
        std::cout << count << std::endl; 
    }

    for(int i = 0; i < wins.size(); i++){
        recurse_wins(i, wins, sum);
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}