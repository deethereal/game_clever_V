//
//  items_functions.cpp
//  game_clever_V
//
//  Created by denis  on 17.11.2020.
//  Copyright © 2020 denis . All rights reserved.
//

#include <stdio.h>
#include "units.h"
#include <iostream>
#include "items.hpp"
#include <map>

extern std::map <std::string, Food> food_list;
extern std::map <std::string, Armor> armory;
extern std::map <std::string, Weapon> weapon;

void delete_it(inventory& from, inventory what)
{
    for (int i=0;i<from.f_part.size();i++)
        for (int j=0;j<what.f_part.size();j++)
            if (what.f_part[i].name==from.f_part[j].name)
                from.f_part[j].count-=what.f_part[i].count;
    for (int i=0;i<from.a_part.size();i++)
        for (int j=0;j<what.a_part.size();j++)
            if (what.a_part[i].name==from.a_part[j].name)
                from.a_part[j].count-=what.a_part[i].count;
    for (int i=0;i<from.w_part.size();i++)
        for (int j=0;j<what.w_part.size();j++)
            if (what.w_part[i].name==from.w_part[j].name)
                from.w_part[j].count-=what.w_part[i].count;
}


void Player::drop_food(std::string name)
{
    for (int i=0;i<f_bag.size();i++)
           if (name==f_bag[i].name)
           {
               std::cout<<"Введите количество, которое хотите выкинуть: N/MAX"<<std::endl;
               std::string counter;
               std::cin>>counter;
               if (counter=="MAX")
               {
                   carrying+=f_bag[i].count*f_bag[i].Food::weight;
                   f_bag.erase(f_bag.begin() + i);
                   std::cout<<"вы выкинули все "<<name<<std::endl;
               }
               else
               {
                   int i_counter=std::stoi( counter );
                   if (i_counter<=f_bag[i].count)
                   {
                       carrying+=i_counter*f_bag[i].Food::weight;
                       f_bag[i].count-=i_counter;
                       std::cout<<"вы выкинули "<<counter<<" "<<name<<std::endl;
                       if (f_bag[i].count==0)
                           f_bag.erase(f_bag.begin() + i);
                   }
                   else
                       std::cout<<"вы не моежете выкинуть столько вещей"<<std::endl;
               }
               return;
           }
    std::cout<<"у вас нет такого предмета"<<std::endl;
    return;
}
void Player::add_item(Armory item)
{
   for (int i=0;i<a_bag.size();i++)
        if (item.name==a_bag[i].name)
        {
            if (carrying-item.weight>=0)
            {
                carrying-=item.weight;
                a_bag[i].count++;
                return;
            }
            else
                std::cout<<"Вы не можете столько поднять"<<std::endl;
            return;
        }
    if (carrying-item.weight>=0)
    {
        carrying-=item.weight;
        a_bag.push_back(item);
        a_bag.back().count++;
        return;
    }
    else
        std::cout<<"Вы не можете столько поднять"<<std::endl;
    return;
    
}
void Player::take_items(inventory from)
{
    for (int i=0;i<from.f_part.size();i++)
    {
        for (int j=0;j<from.f_part[i].count;j++)
            add_food(from.f_part[i]);
    }
    for (int i=0;i<from.a_part.size();i++)
    {
        for (int j=0;j<from.a_part[i].count;j++)
            add_item(from.a_part[i]);
    }
    for (int i=0;i<from.w_part.size();i++)
    {
        for (int j=0;j<from.w_part[i].count;j++)
            add_item(from.w_part[i]);
    }
    //print_invetory();
}
void Player::add_food(Food snack)
{
    for (int i=0;i<f_bag.size();i++)
        if (snack.name==f_bag[i].name)
        {
            if (carrying-snack.Food::weight>=0)
            {
                carrying-=snack.Food::weight;
                f_bag[i].count++;
                
                return;
            }
            else
                std::cout<<"Вы не можете столько поднять"<<std::endl;
            return;
        }
    if (carrying-snack.Food::weight>=0)
    {
        carrying-=snack.Food::weight;
        f_bag.push_back(snack);
        f_bag.back().count++;
        return;
    }
    else
        std::cout<<"Вы не можете столько поднять"<<std::endl;
    return;
    
}
inventory Enemy::mob_drop()
{
    inventory loot_1;
    loot_1.a_part=e_inv.a_part;
    loot_1.f_part=e_inv.f_part;
    loot_1.w_part=e_inv.w_part;
    return loot_1;
}
inventory Unit::create_inv(std::vector<std::pair<std::string, int>> items_list)
{
    inventory loot_1;
    for (int i=0;i<items_list.size();i++)
        {
            auto search1 = food_list.find(items_list[i].first);
            if (search1 != food_list.end())
            {
                loot_1.f_part.push_back(search1->second);
                loot_1.f_part.back().count+=items_list[i].second;
            }
            auto search2 = weapon.find(items_list[i].first);
            if (search2 != weapon.end())
            {
                loot_1.w_part.push_back(search2->second);
                loot_1.w_part.back().count+=items_list[i].second;
            }
            auto search3 = armory.find(items_list[i].first);
            if (search3 != armory.end())
            {
                loot_1.a_part.push_back(search3->second);
                loot_1.a_part.back().count+=items_list[i].second;
            }
        }
    return loot_1;
}
