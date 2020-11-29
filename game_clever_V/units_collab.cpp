//
//  units_collab.cpp
//  game_clever_V
//
//  Created by denis  on 25.11.2020.
//  Copyright © 2020 denis . All rights reserved.
//

#include <stdio.h>
#include "units.h"
#include <iostream>
#include "items.hpp"
#include <vector>

std::vector<std::pair<std::string, int>> string_split(std::string S) //разделял по ","
{
    std::vector<std::pair<std::string, int>> result;
    std::string word="";
    int count_i=0;
    int i=0;
    while (i<S.size())
    {
        while (S[i]!='-')
        {
            word+=S[i];
            i++;
        }
        
        i++;
        while(S[i]!=',' and i<S.size())
        {
            count_i=10*count_i + (int)S[i]-'0';
            i++;
        }
        result.push_back(make_pair(word,count_i));
        word="";
        count_i=0;
        i++;
        
    }
    return result;
}


void p_attack(Enemy& target, Player& p)
{
    if (target.hp_positive())
    {
        inventory mob_drop = target.E_is_alive(p.damage(target, p),p);
        if (mob_drop.is_empty()!=0)
        {
            std::string input="";
            while (input!="-1")
            {
            std::cout<<"цель мертва"<<std::endl;
            mob_drop.show();
            std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество, и т.д.(не советую обманывать)) или info"<<std::endl;
            std::cin>>input;
            while (input=="info")
            {
                p.print_info();
                std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество, и т.д.(не советую обманывать)) или info"<<std::endl;
                std::cin>>input;
            }

            std::vector<std::pair<std::string, int>> inv = string_split(input);
            //проверка на читерство началась(смотрим, что человек взял не больше вещей, чем можно)
            bool cheat=false;
            int j=0;
            while (j< inv.size() and not cheat)
            {
                int i=0;
                while (i<mob_drop.f_part.size() and (not cheat))
                {
                    if ((mob_drop.f_part[i].name==inv[j].first) and (mob_drop.f_part[i].count<inv[j].second))
                    {
                        std::cout<<"Обманывать плохо! Вы остались без вещей!\n";
                        cheat=true;
                    }
                    i++;
                }
                i=0;
                while (i<mob_drop.a_part.size() and (not cheat))
                {
                    if ((mob_drop.a_part[i].name==inv[j].first) and (mob_drop.a_part[i].count<inv[j].second))
                    {
                        std::cout<<"Обманывать плохо! Вы остались без вещей!\n";
                        cheat=true;
                    }
                    i++;
                }
                i=0;
                while (i<mob_drop.w_part.size() and (not cheat))
                {
                    if ((mob_drop.w_part[i].name==inv[j].first) and (mob_drop.w_part[i].count<inv[j].second))
                    {
                        std::cout<<"Обманывать плохо! Вы остались без вещей!\n";
                        cheat=true;
                    }
                    i++;
                }

                j++;
            }
            //проверка на читерство кончилась
            if (not cheat)
            {
                inventory temp=p.create_inv(inv);
                p.take_items(temp);
                std::cout<<"\n";
                delete_it(mob_drop, temp);
            }
            else
                input="-1";
        }
        }
}
}
void Enemy::e_attack(Player& p, Enemy& e)
    {
        p.get_damage(damage(p, e));

    }
