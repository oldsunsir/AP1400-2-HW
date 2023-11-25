#include"espresso_based.h"

void EspressoBased::brew(){}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return this->ingredients;
}

EspressoBased::EspressoBased(){
    this->name = "";
    this->ingredients = std::vector<Ingredient*>{};
}
EspressoBased::EspressoBased(const EspressoBased& esp){
    for (const auto& i : esp.ingredients){
        ingredients.push_back(i->clone());
    }
}
void EspressoBased::operator=(const EspressoBased& esp){
    this->name = esp.name;
    this->ingredients = esp.ingredients;
}
EspressoBased::~EspressoBased(){
    for (const auto& i : ingredients){
        delete i;
    }
    ingredients.clear();
}