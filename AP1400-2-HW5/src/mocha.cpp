#include"mocha.h"

Mocha::Mocha(){
    this->ingredients = std::vector<Ingredient*>{};
    (this->ingredients).push_back(new Espresso(2));
    (this->ingredients).push_back(new Milk(2));
    (this->ingredients).push_back(new MilkFoam(1));
    (this->ingredients).push_back(new Chocolate(1));
    this->side_items = std::vector<Ingredient*>{};
}

Mocha::Mocha(const Mocha& cap) : EspressoBased(cap){
    for (const auto& i : cap.side_items)
        side_items.push_back(i->clone());
}
Mocha::~Mocha(){
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}
void Mocha::operator=(const Mocha& mocha) {
    if (&mocha != this) {
        for (const auto& i : side_items) {
            delete i;
        }
        for (const auto& i : ingredients) {
            delete i;
        }
        ingredients.clear(), side_items.clear();
        for (auto& i : mocha.ingredients) {
            ingredients.push_back(i->clone());
        }
        for (auto& i : mocha.side_items) {
            side_items.push_back(i->clone());
        }
    }
}
std::string Mocha::get_name(){
    return "Mocha";
}
double Mocha::price() {
    double price = 0;
    for (auto x : this->ingredients) {
        price += x->price();
    }
    for (auto x : this->side_items) {
        price += x->price();
    }
    return price;
}
void Mocha::add_side_item(Ingredient* side){
    (this->side_items).push_back(side); 
}
 

std::vector<Ingredient*>& Mocha::get_side_items() { 
    return this->side_items; 
}