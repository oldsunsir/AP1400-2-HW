#ifndef INGREDIENT_H
#define INGREDIENT_H
#include<string>

class Ingredient{
    public:
        double get_price_unit(){
            return price_unit;
        }
        size_t get_units(){
            return this->units;
        }
        double price(){
            return units*price_unit;
        }
        virtual std::string get_name(){
            return this->name;
        }
        virtual Ingredient* clone() = 0;
        virtual ~Ingredient() = default;
    protected:
        Ingredient(double price_unit, size_t units){
            this->price_unit = price_unit;
            this->units = units;
        }
        double price_unit;
        size_t units;
        std::string name;
};
#endif