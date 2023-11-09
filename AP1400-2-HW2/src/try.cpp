#include<map>
#include<string>
using std::map;
int main(){
    map<int ,std::string> myMap{};
    for (auto pair : myMap){pair}
}