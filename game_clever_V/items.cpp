//
//  items.cpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//2
#include "items.hpp"


std::string type[3]={"физ","маг","маг"};
std::string w_name[3]={"ржавый меч", "палка-заклиналка", "ветхая книга"};
int w_strength [3] = {50,10,1};
std::string a_name[3]={"комлпект железных доспехов", "роба школы магии", "церковная роба" };
int w_weight[3]={15,5,1};
int a_protection [3] = {50,15,15};
int a_weight[3]={12,9,3};
std::string f_name[1]={"хлеб"};
int f_weight[1]={2};
int f_satiety[1]={5};

Item::Item() {}
Item::Item(int i) {
    cost = i_cost[i];
}
Armory::Armory()
{}
Weapon::Weapon(){}
Weapon::Weapon(int i)
{
    strength = w_strength[i];
    name = w_name[i];
    weight = w_weight[i];
    type_of_dam = type[i];
}
Armor::Armor(){}
Armor::Armor(int i)
{
    protection = a_protection[i];
    name = a_name[i];
    weight =a_weight[i];
    
}
Food::Food(){}
Food::Food(int name_i, int satiety_i, int weight_i)
{
    count=0;
    weight=f_weight[weight_i];
    satiety = f_satiety[satiety_i];
    name=f_name[name_i];
}
Food::~Food(){}
Item::~Item() {}
Armory::~Armory(){}
Weapon::~Weapon(){}
Armor::~Armor(){}
