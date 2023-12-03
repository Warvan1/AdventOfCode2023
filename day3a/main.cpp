#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

bool checkSymbol(int i, int j, std::vector<std::string>& input){
    if(0 <= i && i < input.size() && 0 <= j && j < input[i].size()){
        if(input[i][j] != '.' && !isdigit(input[i][j])){
            return true;
        }
    }
    return false;
}

int main(){
    int sum = 0;
    std::vector<std::string> input = getInput("input.txt");
    
    for(int i = 0; i < input.size(); i++){
        std::size_t pos = input[i].find_first_of("0123456789");
        while(pos != std::string::npos){
            std::string num;
            int start = pos;
            int size = 0;
            while(isdigit(input[i][pos])){
                num.push_back(input[i][pos]);
                pos++;
                size++;
            }

            bool symbol = false;
            for(int j = start-1; j < start+size+1 && !symbol; j++){
                symbol = checkSymbol(i-1, j, input);
            }
            if(!symbol) symbol = checkSymbol(i, start-1, input);
            if(!symbol) symbol = checkSymbol(i, start+size, input);
            for(int j = start-1; j < start+size+1 && !symbol; j++){
                symbol = checkSymbol(i+1, j, input);
            }

            if(symbol) sum += stoi(num);

            pos = input[i].find_first_of("0123456789", pos+1);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}