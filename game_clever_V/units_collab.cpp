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
#include <map>
#include <unistd.h>

extern std::map <std::string, Food> food_list;
extern std::map <std::string, Armor> armory;
extern std::map <std::string, Weapon> weapon;

std::vector<std::pair<std::string, int>> string_split(const std::string& S) //разделял по ","
{
    std::vector<std::pair<std::string, int>> result;
    std::string word="";
    //std::cout<<S<<"\n";
    //std::cout<<S[1]<<std::endl;
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
    int flag = 0;
    if (target.hp_positive())
    {
        inventory mob_drop = target.E_is_alive(p.damage(target, p),p,i);
        if (mob_drop.is_empty()!=0)
        {
            std::string input="info";
            while (input!="стоп")
            {
            if (flag==1)
            {
            std::cout<<"\nЦЕЛЬ МЕРТВА\n"<<std::endl; //выяснить почему два раза выводится 
            mob_drop.show();
            std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество, и т.д.(не советую обманывать)) или info, или стоп"<<std::endl;
            }
                std::getline(std::cin,input);
            if (flag==1)
            {
            while (input=="info")
            {
                p.show_inv();
                std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество, и т.д.(не советую обманывать)) или info, или стоп"<<std::endl;
                std::getline(std::cin,input);
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
                std::cout<<"\nТеперь у вас "<<p.return_money()<<" монет\n";
            }
            else
                input="-1";
        }
        flag=1;
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
            u.e_attack(p, u);
        }
    }
}
void fNPC::sell(Player& p)
{
    
    std::vector<std::pair<std::string, int>> inv;
    bool cheat=true;
    std::string input="info";
    int flag=0;
    while (cheat and input!="стоп")
    {
        
        if (flag==1)
        {
            std::cout<<"Ваши вещи:\n";
            p.show_inv();
            std::cout<<std::endl;
            std::cout<<"На продажу есть:\n";
            npc_inv.show_for_selling();
            std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество) или info, или стоп"<<std::endl;
        }
        std::getline(std::cin,input);
        if (flag ==1)
        {
        
        while (input=="info")
        {
            p.show_inv();
            std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество через запятую без пробелов) или info, или стоп\n"<<std::endl;
            std::getline(std::cin,input);
        }
        std::vector<std::pair<std::string, int>> inv = string_split(input);
        cheat=false;
        //проверка на то, что вещей достаточно
        int j=0;
        if (input!="стоп")
        {
        while (j< inv.size() and not cheat)
        {
            int i=0;
            while (i<npc_inv.f_part.size() and (not cheat))
            {
                if ((npc_inv.f_part[i].name==inv[j].first) and (npc_inv.f_part[i].count<inv[j].second))
                {
                    std::cout<<"У меня нет столько вещей!\n";
                    cheat=true;
                }
                i++;
            }
            i=0;
            while (i<npc_inv.a_part.size() and (not cheat))
            {
                if ((npc_inv.a_part[i].name==inv[j].first) and (npc_inv.a_part[i].count<inv[j].second))
                {
                    std::cout<<"У меня нет столько вещей!\n";
                    cheat=true;
                }
                i++;
            }
            i=0;
            while (i<npc_inv.w_part.size() and (not cheat))
            {
                if ((npc_inv.w_part[i].name==inv[j].first) and (npc_inv.w_part[i].count<inv[j].second))
                {
                    std::cout<<"У меня нет столько вещей!\n";
                    cheat=true;
                }
                i++;
            }

            j++;
        }
        
    if (not cheat)
    {
        inventory temp=p.create_inv(inv);
        float sum=0;
        int i=0;
        while (i<temp.f_part.size()) {
            float cost_i=0;
            for (int j=0;j<npc_inv.f_part.size();j++)
            {
                if (temp.f_part[i].name==npc_inv.f_part[j].name)
                    cost_i=npc_inv.f_part[j].cost;
            }
            sum+=(temp.f_part[i].count*cost_i);
            i++;
        }
        i=0;
        while (i<temp.w_part.size()) {
            float cost_i=0;
            for (int j=0;j<npc_inv.w_part.size();j++)
            {
                if (temp.w_part[i].name==npc_inv.w_part[j].name)
                    cost_i=npc_inv.w_part[j].cost;
            }
            sum+=(temp.w_part[i].count*cost_i);
            i++;
        }
        i=0;
        while (i<temp.a_part.size()) {
            float cost_i=0;
            for (int j=0;j<npc_inv.a_part.size();j++)
            {
                if (temp.a_part[i].name==npc_inv.a_part[j].name)
                    cost_i=npc_inv.a_part[j].cost;
            }
            sum+=(temp.a_part[i].count*cost_i);
            i++;
        }
        if (p.return_money()>=sum)
        {
            p.money_decrease(sum);
            money_increase(sum);
            p.take_items(temp);
            std::cout<<"\n";
            delete_it(npc_inv, temp);
        }
        else{
            
            std::cout<<"Вам не хватает денег\n";
        }
        cheat=true;
    }
    }
    }
        if (flag==1)
            sleep(3);
        else
            flag=1;
    }
}
void sell_to_npc(fNPC& seller, Player& p)
{
    
    std::vector<std::pair<std::string, int>> inv;
    bool cheat=true;
    std::string input="";
    while (cheat and input!="стоп")
    {
        std::cout<<"У торговца есть "<<seller.return_money()<<"  монет\n";
        p.print_invetory(true);//передается нужно ли выводить стоимость
        std::cout<<"\nВведите название вещей и количество, которое хотите продать(вещь-количество) или info\n или стоп\n";
        std::getline(std::cin,input);
        while (input=="info")
        {
            p.print_invetory(true);//передается нужно ли выводить стоимость
            std::cout<<"Введите название вещей и количество, которое хотите продать(вещь-количество через запятую без пробелов) или info или стоп\n"<<std::endl;
            std::getline(std::cin,input);
        }
        std::vector<std::pair<std::string, int>> inv = string_split(input);
        cheat=false;
        if (input!="стоп")
        {
            int j=0;
            while (j< inv.size() and not cheat)
            {
                int i=0;
                while (i<p.f_bag.size() and (not cheat))
                {
                    if ((p.f_bag[i].name==inv[j].first) and (p.f_bag[i].count<inv[j].second))
                    {
                        std::cout<<"У вас нет столько вещей!\n";
                        cheat=true;
                    }
                    i++;
                }
                i=0;
                while (i<p.a_bag.size() and (not cheat))
                {
                    if ((p.a_bag[i].name==inv[j].first) and (p.a_bag[i].count<inv[j].second))
                    {
                        std::cout<<"У вас нет столько вещей!\n";
                        cheat=true;
                    }
                    i++;
                }

                j++;
            }
            if (not cheat)
            {
                inventory temp=p.create_inv(inv);
                float sum=0;
                int i=0;
                while (i<temp.f_part.size()) {
                    float cost_i=0;
                    for (int j=0;j<p.f_bag.size();j++)
                    {
                        if (temp.f_part[i].name==p.f_bag[j].name)
                            cost_i=p.f_bag[j].cost;
                    }
                    sum+=(temp.f_part[i].count*cost_i);
                    i++;
                }
                i=0;
                while (i<temp.w_part.size()) {
                    float cost_i=0;
                    for (int j=0;j<p.a_bag.size();j++)
                    {
                        if (temp.w_part[i].name==p.a_bag[j].name)
                            cost_i=p.a_bag[j].cost;
                    }
                    sum+=(temp.w_part[i].count*cost_i);
                    i++;
                }
                i=0;
                while (i<temp.a_part.size()) {
                    float cost_i=0;
                    for (int j=0;j<p.a_bag.size();j++)
                    {
                        if (temp.a_part[i].name==p.a_bag[j].name)
                            cost_i=p.a_bag[j].cost;
                    }
                    sum+=(temp.a_part[i].count*cost_i);
                    i++;
                }
                if (seller.return_money()>=sum)
                {
                    p.money_increase(sum);
                    seller.money_decrease(sum);
                    std::cout<<"вы заработали "<<sum<<" монет!\n";
                    seller.add_items(temp);
                    std::cout<<"\n";
                    p.delete_part(temp);
                }
                else{
                    
                    std::cout<<"У продавца не хватает денег\n";
                }
                cheat=true;
            }
            
            
            
            
            
        }
        
        sleep(3);

    }
    
}
