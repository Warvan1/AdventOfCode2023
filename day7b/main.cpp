#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

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

//convert a card char to a num representing value
int cardToNum(char c){
    if(c == 'A'){
        return 14;
    }
    if(c == 'K'){
        return 13;
    }
    if(c == 'Q'){
        return 12;
    }
    if(c == 'J'){
        return 0;
    }
    if(c == 'T'){
        return 10;
    }
    return c - '0';
}

class Hand{
    public:

    //construct a hand
    Hand(std::string a, int b){
        hand = a;
        bid = b;
        rank = -1;
    }

    //return the rank for a given hand
    int rankHand(){
        if(rank != -1){
            return rank;
        }

        //create map of each card in the hand to how many times it appears in the hand
        std::map<char, int> counts;
        for(char c : hand){
            std::map<char, int>::iterator it = counts.find(c);
            if(it == counts.end()){
                counts.insert(std::pair<char, int>(c,1));
            }
            else{
                it->second++;
            }
        }

        //add the number of J cards to each other card and then remove the j cards from the map
        for(std::map<char, int>::iterator it = counts.begin(); it != counts.end(); it++){
            if(it->first == 'J'){
                for(std::map<char, int>::iterator it2 = counts.begin(); it2 != counts.end(); it2++){
                    if(it2->first != 'J'){
                        it2->second += it->second;
                    }
                }
                counts.erase('J');
                break;
            }
        }

        if(counts.size() <= 1){
            rank = 6; // 5 of a kind
            return rank; 
        }
        if(counts.size() == 2){
            for(std::map<char, int>::iterator it = counts.begin(); it != counts.end(); it++){
                if(it->second == 4){
                    rank = 5; // 4 of a kind
                    return rank; 
                }
            }
            rank = 4;
            return rank; // full house
        }
        if(counts.size() == 3){
            for(std::map<char, int>::iterator it = counts.begin(); it != counts.end(); it++){
                if(it->second == 3){
                    rank = 3; // 3 of a kind
                    return rank; 
                }
            }
            rank = 2; // 2 pair
            return rank; 
        }
        if(counts.size() == 4){
            rank = 1; // 1 pair
            return rank; 
        }
        rank = 0; // high card
        return 0; 
    }

    //data
    std::string hand;
    int bid;
    int rank;
};

//used in the sort function to compare two hands and return the worse hand
bool compare_hands(Hand a, Hand b) {
    if(a.rank < b.rank){
        return true;
    }
    if(a.rank > b.rank){
        return false;
    }
    for(int i = 0; i < a.hand.size(); i++){
        if(a.hand[i] != b.hand[i]){
            int x = cardToNum(a.hand[i]);
            int y = cardToNum(b.hand[i]);
            return x < y;
        }
    }
    return true;
}

int main(){
    std::fstream f("input.txt");
    std::string line;
    u_int64_t sum = 0;
    std::vector<Hand> hands;

    while(getline(f, line)){
        std::vector<std::string> input = split(line, ' ');
        Hand hand(input[0], stoi(input[1]));
        hand.rankHand();
        hands.push_back(hand);
    }

    //sort hands using custom sort function
    std::sort(hands.begin(), hands.end(), compare_hands);

    int i = 1;
    for(Hand h : hands){
        std::cout << h.hand << " " << h.bid << " " << h.rank << std::endl;
        sum += h.bid * i;
        i++;
    }

    std::cout << sum << std::endl;

    f.close();
    return 0;
}