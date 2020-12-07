//
//  items.hpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//3

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
    
    
    
public:
    int protection;
    Armor();
    Armor(int i);
    ~Armor();
};
class Food:public Item
{
protected:

public:
    int count;
    Food();
    int satiety;
    Food(int name_i, int satiety_i, int weight_i );
    ~Food();
};
#endif /* items_hpp */
