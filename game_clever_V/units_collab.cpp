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


void p_attack(Enemy& target, Player& p,int i)
{
    if (target.hp_positive())
    {
        inventory mob_drop = target.E_is_alive(p.damage(target, p),p,i);
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
                p.money_increase(target.return_money());
                std::cout<<"\nТеперь у вас"<<p.return_money()<<" монет\n";
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

void fight_pve(Player& p, Enemy& u, int i)
{
    while (u.hp_positive() and p.is_alive()) {
        int a=rand()%101 +1;
        int b=rand()%101 +1;
        std::cout<<"Cколько будет "<<a<<"*"<<b<<"\n";
        std::string m_a;
        std::cin >>m_a;
        if (m_a=="info")
        {
            p.print_info();
            
        }
        else if (m_a=="поесть")
        {
            std::cout<<"что вы хотите съесть?"<<std::endl;
            p.print_invetory();
            std::string snack;
            std::cin>>snack;
            p.have_a_dinner(snack);
        }
        else if (isdigit(m_a[0]))
        {
            if (stof(m_a)==a*b)
            {
                std::cout<<"Верно\n";
                p_attack(u, p,i);
            }

            else std::cout<<"Неверно\n";
            p.fatigue();
        }
        else
        {
            while (!isdigit(m_a[0]))
            {
                std::cout<<"Это не число, введите число\n";
                std::cin>>m_a;
            }
            if (stof(m_a)==a*b)
            {
                std::cout<<"Верно\n";
                p_attack(u, p, i);
            }

            else std::cout<<"Неверно\n";
            p.fatigue();
        }
        if (u.hp_positive())
        {
            std::cout<<"Теперь атакует противник\n";
            u.e_attack(p, u);//починить
        }
    }
}
