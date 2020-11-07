//
//  items.hpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//

#ifndef items_hpp
#define items_hpp
#include "string"
#include <stdio.h>
#include <iostream>
#include <vector>

class Item
{
protected:
    int i_cost[1]={10};
    //int rarity;
public:
    int weight;
    int count;
    int cost;
    std::string name;
    int sell(int stoimost);
    Item();
    Item(int i);
    ~Item();
    
};
class Armory: public Item
{
protected:
public:
    Armory();
    ~Armory();
};
class Weapon :public Armory
{
protected:
    std::string w_name[3]={"ржавый меч", "палка-заклиналка", "ветхая книга"};
    int w_strength [3] = {50,10,1};
   
    int w_weight[3]={15,5,1};
    
    std::string type[3]={"физ","маг","маг"};
public:
    std::string type_of_dam;
    int strength;
    Weapon();
    Weapon(int i);
    ~Weapon();
};

class Armor: public Armory
{
protected:
    std::string a_name[3]={"комлпект железных доспехов", "роба школы магии", "церковная роба" };
    int a_protection [3] = {50,15,15};
    int a_weight[3]={12,9,3};
    
    
public:
    int protection;
    Armor();
    Armor(int i);
    ~Armor();
};
class Food:public Item
{
protected:
     std::string f_name[1]={"хлеб"};
     int f_weight[1]={2};
     int f_satiety[1]={5};
public:
    int count;
    Food();
    int satiety;
    Food(int name_i, int satiety_i, int weight_i );
    ~Food();
};
#endif /* items_hpp */
