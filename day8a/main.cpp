#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

struct Map{
    std::string left;
    std::string right;
};

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
    u_int64_t sum = 0;
    std::string path;
    std::unordered_map<std::string, Map> maps;

    while(getline(f, line)){
        std::vector<std::string> input = split(line, ' ');
        if(input.size() == 4){
            Map map;
            map.left = input[2].substr(1,3);
            map.right = input[3].substr(0,3);
            maps[input[0]] = map;
        }
        else if(input[0] != ""){
            path = input[0];
        }
    }

    int pathIndex = 0;
    std::string loc = "AAA";
    while(loc != "ZZZ"){
        Map map = maps[loc];
        if(path[pathIndex] == 'L'){
            loc = map.left;
        }
        else{
            loc = map.right;
        }
        pathIndex++;
        if(pathIndex == path.length()){
            pathIndex = 0;
        }
        sum++;
        std::cout << loc << " " << pathIndex << " " << path[pathIndex] << std::endl;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}