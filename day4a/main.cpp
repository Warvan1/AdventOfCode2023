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

int main(){
    std::fstream f("input.txt");
    std::string line;
    int sum = 0;
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
                if(count == 0){
                    count++;
                }
                else{
                    count = count*2;
                }
            }
            else if(winning[i] < nums[j]){
                i++;
            }
            else{
                j++;
            }
        }

        sum += count;
        std::cout << count << " " << sum << std::endl; 

    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}