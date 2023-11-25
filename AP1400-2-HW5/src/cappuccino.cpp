#include"cappuccino.h"

Cappuccino::Cappuccino(){
    this->ingredients = std::vector<Ingredient*>{};
    (this->ingredients).push_back(new Espresso{2});
    (this->ingredients).push_back(new Milk{2});
    (this->ingredients).push_back(new MilkFoam{1});
    this->side_items = std::vector<Ingredient*>{};
}
Cappuccino::~Cappuccino(){
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}
std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return this->side_items;
}
//这里记得也要copy基类
Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap){
    name = cap.name;
    for (const auto& i : cap.side_items)
        side_items.push_back(i->clone());
}

void Cappuccino::operator=(const Cappuccino& cap){
    if (&cap != this){
        for (const auto& i : side_items)
            delete i;
        for (const auto& i : ingredients)
            delete i;
        ingredients.clear(), side_items.clear();
        for (const auto& i : cap.ingredients){
            ingredients.push_back(i->clone());
        }
        for (const auto& i : cap.side_items){
            side_items.push_back(i->clone());
        }
    }
}
std::string Cappuccino::get_name(){
    return "Cappuccino";
}
double Cappuccino::price(){
    double price = 0;
    for (auto x : this->ingredients)
        price += x->price();
    for (auto x : this->side_items)
        price += x->price();
    return price;
}
void Cappuccino::add_side_item(Ingredient* side){
    (this->side_items).push_back(side);
}