#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <thread>
#include <mutex>

std::mutex tLock;

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

void check_range_seed(std::vector<std::vector<std::vector<long long>>>& almanac, std::vector<long long>& minArr, long long start, long long stop, int id){
    std::cout << id << std::endl;
    long long min = 9223372036854775807;
    for(long long j = start; j < stop; j++){
        long long s = j;
        for(int k = 0; k < almanac.size(); k++){
            s = check_almanac(almanac[k], s);
        }
        min = std::min(min, s);
    }
    tLock.lock();
    minArr.push_back(min);
    tLock.unlock();
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

    std::vector<long long> minArr;
    for(int i = 0; i < seeds.size(); i += 2){
        std::cout << seeds[i] << " " << seeds[i+1] << std::endl;
        int numThreads = 16;
        long long start = seeds[i];
        long long size = seeds[i+1];
        long long interval = size/numThreads;
        long long remainder = size % numThreads;
        std::vector<std::thread> threads;

        for(int i = 0; i < numThreads; i++){
            long long stop = start + interval;
            if(i == numThreads -1){
                stop += remainder;
            }
            threads.push_back(std::thread(check_range_seed, std::ref(almanac), std::ref(minArr), start, stop, i));
            start += interval;
        }
        for(std::thread &t : threads){
            t.join();
        }
    }

    std::vector<long long>::iterator result = std::min_element(minArr.begin(), minArr.end());
    std::cout << *result << std::endl;

    f.close();
    return 0;
}