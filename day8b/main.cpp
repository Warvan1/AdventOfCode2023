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

struct MapLoop{
    std::string loc = "";
    std::string start = "";
    std::string end = "";
    int loopSize = 0;
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

std::vector<MapLoop> startLoc(std::unordered_map<std::string, Map> maps){
    std::vector<MapLoop> locs;
    for(auto it = maps.begin(); it != maps.end(); it++){
        if(it->first[2] == 'A'){
            MapLoop loop;
            loop.start = it->first;
            loop.loc = loop.start;
            locs.push_back(loop);
        }
    }
    return locs;
}

int main(){
    std::fstream f("input.txt");
    std::string line;
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
    std::vector<MapLoop> locs = startLoc(maps);
    for(int i = 0; i < locs.size(); i++){
        while(locs[i].end == ""){
            Map map = maps[locs[i].loc];
            if(path[pathIndex] == 'L'){
                locs[i].loc = map.left;
            }
            else{
                locs[i].loc = map.right;
            }
            locs[i].loopSize++;
            pathIndex++;
            if(pathIndex == path.length()){
                pathIndex = 0;
            }
            if(locs[i].loc[2] == 'Z'){
                locs[i].end = locs[i].loc;
            }
        }

        //print ml
        std::cout << locs[i].start << " " << locs[i].end << " " << locs[i].loopSize << std::endl;
        std::cout << "-----------------" << std::endl;
    }

    u_int64_t lcm = 1;
    for(MapLoop ml: locs){
        u_int64_t size = ml.loopSize;
        u_int64_t a;
        u_int64_t b;
        u_int64_t rem;
        if(lcm > size){
            a = lcm;
            b = size;
        }
        else {
            a = size;
            b = lcm;
        }

        while(b != 0){
            rem = a % b;
            a = b;
            b = rem;
        }
        //a is now the greatest common denominator
        lcm = lcm * size / a;
    }

    std::cout << lcm << std::endl;

    f.close();
    return 0;
}