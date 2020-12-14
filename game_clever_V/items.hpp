//
//  items.hpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//3

#ifndef items_hpp
#define items_hpp


#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
class Item
{
protected:
    float i_cost[6]={0.5,5,40,100,1,80};
    //int rarity;
public:
    int weight;
    int count=0;
    float cost;
    std::string name;
    int sell(int stoimost);
    Item();
    ~Item();
    
};
class Armory: public Item
{
public:
    Armory();
    bool equal(Armory one);
    ~Armory();
};
class Weapon :public Armory
{
public:
    std::string type[4]={"физ","маг","маг","физ"};
    std::string w_name[4]={"ржавый меч", "палка заклиналка", "ветхая книга","нож"};
    int w_strength [4] = {50,10,1,25};
    int w_weight[4]={15,5,1,5};
    std::string type_of_dam;
    int strength;
    Weapon();
    Weapon(int i,int abscost_id);
    ~Weapon();
};

class Armor: public Armory
{
public:
    int a_protection [3] = {50,15,15};
    int a_weight[3]={12,9,3};
    std::string a_name[3]={"комлпект железных доспехов", "роба школы магии", "церковная роба" };
    int protection;
    Armor();
    Armor(int i,int abscost_id);
    ~Armor();
};
class Food:public Item
{
public:
    int f_weight[2]={2,1};
    int f_satiety[2]={5,8};
    std::string f_name[2]={"хлеб","яблоко"};
    Food();
    int satiety;
    Food(int name_i, int satiety_i, int weight_i,int abscost_id );
    ~Food();
};



#endif /* items_hpp */
