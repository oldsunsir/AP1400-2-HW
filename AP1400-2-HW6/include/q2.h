#ifndef Q2_H
#define Q2_H
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
using std::string;
using std::stringstream;
using std::stoul;
namespace q2{

    struct Patient{
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
        size_t risks;
    };
    std::vector<Patient> read_file(std::string filename);
    void sort(std::vector<Patient>& p);
    std::vector<Patient> read_file(std::string filename){
        std::vector<Patient>res;
        std::ifstream f(filename);
        if (!f){
            throw std::runtime_error("open file error");
        }
        string line;
        int i = 0;
        while (getline(f, line)){
            if (i < 2){
                i++;
                continue;
            }
            else{
                stringstream ss(line);
                string field;
                string name = "";
                int mark = 0;
                std::vector<string> row;
                while (getline(ss, field, ',')){
                    if (mark == 0){
                        field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                        name += field;
                        mark++;
                    } else if (mark == 1){
                        field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                        name += " ";
                        name += field;
                        mark++;
                    } else{
                        row.push_back(field);
                    }
                }
                Patient p{name, stoul(row[0]),stoul(row[1]), stoul(row[2]), stoul(row[3])};
                p.risks = 3*p.age + 5* p.smokes + 2*p.area_q + 4*p.alkhol;
                res.push_back(p);
            }
        }
        f.close();
        return res;
    }

    void sort(std::vector<Patient>& p){
        std::sort(p.begin(), p.end(), [](const Patient& p1, 
                            const Patient& p2)->bool{
                                return p1.risks >= p2.risks;
                            });
    }
}

#endif