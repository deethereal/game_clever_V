//
//  items_functions.cpp
//  game_clever_V
//
//  Created by denis  on 17.11.2020.
//  Copyright © 2020 denis . All rights reserved.
//

#include <stdio.h>
#include "units.h"
#include "items.hpp"
void Player::drop_food(std::string name)
{
    for (int i=0;i<f_bag.size();i++)
           if (name==f_bag[i].name)
           {
               std::cout<<"Введите количество, которое хотите выкинуть: N/MAX"<<std::endl;
               // ДОПИСАТЬ ВЕСА ДЛЯ ВЕЩЕЙ И ПЕРЕГРУЗ ЧЕЛИКА
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
    print_invetory();
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

