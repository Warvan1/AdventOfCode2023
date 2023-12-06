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

long long check_almanac(std::vector<std::vector<long long>>& table, long long source){
    for(int i = 0; i < table.size(); i++){
        if(table[i][1] <= source && source < table[i][1] + table[i][2]){
            return table[i][0] + (source - table[i][1]);
        }
    }
    return source;
}

int main(){
    std::fstream f("input.txt");
    std::string line;
    std::vector<long long> seeds;
    std::vector<std::vector<std::vector<long long>>> almanac;
    int mapindex = -1;

    
    while(getline(f, line)){
        std::vector<std::string> input = split(line, ' ');
        if(input.size() <= 1);
        else if(input[0] == "seeds:"){
            for(int i = 1; i < input.size(); i++){
                seeds.push_back(stoll(input[i]));
            }
        }
        else if(!isdigit(input[0][0])){
            mapindex++;
            almanac.push_back({});
        }
        else{
            std::vector<long long> line_ll;
            for(int i = 0; i < input.size(); i++){
                line_ll.push_back(stoll(input[i]));
            }
            almanac[mapindex].push_back(line_ll);
        }
    }

    for(int i = 0; i < almanac.size(); i++){
        for(int j = 0; j < seeds.size(); j++){
            seeds[j] = check_almanac(almanac[i], seeds[j]);
        }
    }
    
    std::vector<long long>::iterator result = std::min_element(seeds.begin(), seeds.end());
    std::cout << *result << std::endl;

    f.close();
    return 0;
}