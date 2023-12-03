#ifndef Q3_H
#define Q3_H

#include<vector>
#include<string>
#include<queue>
#include<algorithm>
#include<sstream>

namespace q3{
    using std::cout;
    using std::endl;
    using std::ifstream;
    using std::priority_queue;
    using std::stoul;
    using std::string;
    using std::stringstream;
    using std::vector;

    struct Flight{
        string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
        size_t sum = (int)duration + (int)connection_times + 
                3 * (int)price;
        bool operator<(const Flight& f) const{
            return sum > f.sum;
        }
    };
    size_t exchange_time(string s){
        size_t time = 0;
        auto start = 0;
        auto end = s.find('h');
        string tmp = s.substr(start, end-start);
        time = std::stoi(tmp) * 60;

        if (s.find('m') == string::npos){
            return time;
        }
        start = end+1;
        end = s.find('m');
        time += std::stoi(s.substr(start, end-start));
        return time;
    }
    vector<string> split(const string& s, char delim){
        vector<string> res;
        size_t start = 0;
        size_t end = s.find(delim);
        while (end != string::npos){
            string tmp = s.substr(start, end - start);
            if (tmp.length() < 5){
                start = end+1;
                end = s.find(delim, start);
                continue;
            }else{
                tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end());
                res.push_back(tmp);
                start = end+1;
                end = s.find(delim, start);
            }
        }
        string temp = s.substr(start);
        temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
        res.push_back(temp);
        return res;
    }

    string clean_up(string s){
        auto start = s.find(":") + 1;
        string temp = s.substr(start);
        temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
        return temp;
    }
    size_t get_duration(string s){
        s = clean_up(s);
        return exchange_time(s);
    }
    size_t get_connection_time(string s){
        s = clean_up(s);
        size_t time = 0;
        vector<string> sp;
        size_t start = 0;
        size_t end = s.find(',');
        while (end != string::npos){
            string tmp = s.substr(start, end - start);
            sp.push_back(tmp);
            start = end+1;
            end = s.find(',', start);
        }
        sp.push_back(s.substr(start));
        for (auto x : sp){
            time += get_duration(x);
        }
        return time;
    }
    size_t get_connection(string s){
        s = clean_up(s);
        auto start = 0;
        return stoi(s.substr(start));
    }
    size_t get_price(string s){
        s = clean_up(s);
        return stoi(s);
    }
    priority_queue<Flight>gather_flights(string filename){
        priority_queue<Flight> res;
        ifstream f(filename);
        if (!f){
            throw std::runtime_error("can't open file");
        }
        string line;
        while (getline(f, line)){
            auto m = split(line, '-');

            auto number = clean_up(m[0]);
            auto duration = get_duration(m[1]);
            auto connection = get_connection(m[2]);
            auto connection_time = get_connection_time(m[3]);
            auto price = get_price(m[4]);

            Flight f1{number, duration, connection, connection_time, price};
            res.push(f1);
        }
        f.close();
        return res;
    }
}

#endif