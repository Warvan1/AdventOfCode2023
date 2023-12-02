#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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
    int i = 1;
    while(getline(f, line)){
        bool goodGame = true;
        std::vector<std::string> games = split(line, ' ');
        for(int i = 2; i < games.size(); i+= 2){
            if(games[i+1][0] == 'r'){
                if(stoi(games[i]) > 12){
                    goodGame = false;
                }
            }
            else if(games[i+1][0] == 'g'){
                if(stoi(games[i]) > 13){
                    goodGame = false;
                }
            }
            else if(games[i+1][0] == 'b'){
                if(stoi(games[i]) > 14){
                    goodGame = false;
                }
            }
        }
        
        if(goodGame){
            sum += i;
        }
        i++;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}