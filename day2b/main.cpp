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
        std::vector<std::string> games = split(line, ' ');
        int rmin = 0;
        int gmin = 0;
        int bmin = 0;
        for(int i = 2; i < games.size(); i+= 2){
            if(games[i+1][0] == 'r'){
                rmin = std::max(stoi(games[i]), rmin);
            }
            else if(games[i+1][0] == 'g'){
                gmin = std::max(stoi(games[i]), gmin);
            }
            else if(games[i+1][0] == 'b'){
                bmin = std::max(stoi(games[i]), bmin);
            }
        }

        sum += rmin*gmin*bmin;
        std::cout << rmin << " " << gmin << " " << bmin << std::endl;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}