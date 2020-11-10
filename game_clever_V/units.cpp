//
//  units.cpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//5

#include <stdio.h>
#include <string>
#include <iostream>
#include "units.h"
#include "items.hpp"
#include <map>


std::map <std::string, Armor> armory = {{"c_base", Armor(2)}, {"m_base", Armor(1)}, {"w_base", Armor(0)}};
std::map <std::string, Weapon> weapon = {{"c_base", Weapon(2)}, {"m_base", Weapon(1)}, {"w_base", Weapon(0)}};
std::map <std::string, Food> food_list={{"bread", Food(0,0,0)} };


Unit::Unit()
{
}
Enemy::Enemy()
{
}

Enemy::Enemy(std::string race, int hp, int experience_,int power, int arm, std::string type_drop, std::vector<std::string> drop_id_f,std::vector<std::string> drop_id_w, std::vector<std::string> drop_id_a )
{
    e_race= race;
    MAX_HEALTH=hp;
    health = hp;
    experience=experience_;
    p_ar.first.strength=power;
    p_ar.second.protection=arm;
    bool we=false;
    bool ar=false;
    bool fo=false;
    for (int i=0;i<type_drop.length();i++)
    {
        if (type_drop[i]=='w')
            we=true;
        if (type_drop[i]=='a')
            ar=true;
        if (type_drop[i]=='f')
            fo=true;
            }
        if (we)
            for (int i=0;i<drop_id_w.size();i++)
                w_inv.push_back(weapon.find(drop_id_w[i])->second);
        if (ar)
            for (int i=0;i<drop_id_a.size();i++)
                a_inv.push_back(armory.find(drop_id_a[i])->second);
        if (fo)
             for (int i=0;i<drop_id_f.size();i++)
                f_inv.push_back(food_list.find(drop_id_f[i])->second);
}
void Enemy::E_is_alive(int g_damage)
{
    //get_damage(g_damage);
    if (health<=0)
    {
        std::cout<<"цель мертва"<<std::endl;
        if (e_race=="гуманоид" or e_race=="зверь" or e_race=="БОСС" or e_race=="нeжить")
        {
            std::cout<<"drop"<<std::endl;
            //mob_drop();
        }
        level.level_bar+=experience;
        level.lvlup();
        level.progress(experience);
    }
    else
        std::cout<<"осталоcь "<<MAX_HEALTH-g_damage<<" здоровья"<<std::endl;
}
inventory Enemy::mob_drop()
{
    inventory loot_1;
    loot_1.a_part=a_inv;
    loot_1.f_part=f_inv;
    loot_1.w_part=w_inv;
    return loot_1;
}
Player::Player()
{
    std::cout<<"Введите класс: маг/воин/клерик "<<std::endl;
    std::cin>>clas;
    if (!(clas=="маг" or clas=="воин" or clas =="клерик"))
    {
        while (!(clas=="маг" or clas=="воин" or clas =="клерик")) {
            std::cout<<"Это не класс. Введите класс: маг/воин/клерик "<<std::endl;
            std::cin>>clas;
            
        }
        
    }
    std::cout<<"Введите имя"<<std::endl;
    std::cin>>name;
    std::cout<<"Введите гендер"<<std::endl;
    std::cin>>gender;
    std::cout<<"Выберите расу"<<std::endl;
    for(int i=0;i<8;i++)
        std::cout<<race[i]<<" ";
    std::cout<<std::endl;
    std::string mb_race;
    int temp = -1;
    while (temp!=1)
    {
    std::cin>>mb_race;
    for(int i=0;i<8;i++)
        if (mb_race == race[i])
        {
            temp=1;
            break;
        }
    if (temp==-1)
        std::cout<<"Это не являтеся расой, выберите одну из предложенных"<<std::endl;
    }
    p_race=mb_race;
    if (p_race=="дракон")
        MAX_HEALTH=120; //поменять в хилинг!!!!
    else
        MAX_HEALTH=100;
    health=MAX_HEALTH;
    if (p_race=="дворф")
        armor=10;
    else
        armor=0;
    if (p_race=="гоблин")
        money = 50;
    if (p_race=="орк")
        physic_damage+=3;
    if (p_race=="эльф")
        magic_damage+=3;
    if (p_race=="троль")
        p_mult=0.1;
    else
        money=5;
    hunger=0;
   
    level.level=1;
    level.level_bar=0;
    if (clas=="воин")
    {
        magic_damage-=20;
        physic_damage+=5;
        p_mult+=0.25;
        max_carrying=50;
        carrying=max_carrying;
        p_ar.first=(weapon.find("w_base"))->second;
        p_ar.second=armory.find("w_base")->second;
    }
    else if (clas=="маг")
    {
        magic_damage+=5;
        max_carrying=40;
        carrying=max_carrying;
        p_ar.first=weapon.find("m_base")->second;
        p_ar.second=armory.find("m_base")->second;
    }
    else if (clas=="клерик")
    {
        p_mult+=1;
        magic_damage-=5;
        max_carrying=29;
        carrying=max_carrying;
        p_ar.first=weapon.find("c_base")->second;
        p_ar.second=armory.find("c_base")->second;
    }
    std::cout<<typeid(a_bag[0]).name()<<std::endl;
    if (p_race=="каджит")
        add_food(food_list.find("bread")->second);
    add_food(food_list.find("bread")->second);
}
int Player::pray(int target)
{
    int damage=20;
    if (target==0)
    {
        
        return p_mult*damage;
    }
    std::cout<<"Вы нанесли "<<p_mult*damage<<" урона "<<std::endl;
    return p_mult*damage;

}
bool Player::is_alive()
{
    if (health>0)
        return true;
    std::cout<<"Вы умерли"<<std::endl;
    return false;
}
bool Player::is_hungry()
{
    if (hunger>=-100)
        return true;
    if (hunger==-80)
        std::cout<<"Вы начинаете голодать"<<std::endl;
    std::cout<<"Вы голодны"<<std::endl;
    health-=10;
    return false;
}
void Unit::get_damage(int damage)
{
    health-=damage;
}

int Unit::damage(Unit& target, Unit& attacker)
{
    int mhp=attacker.p_ar.first.strength;
    if (attacker.p_ar.first.type_of_dam == "физ")
    {
        mhp+=attacker.physic_damage;
        mhp=mhp-(target.p_ar.second.protection)/2;
        target.get_damage(mhp);
        std::cout<<"Цель получила "<<mhp<<" урона"<<std::endl;
    }
    else
    {
        mhp+=attacker.magic_damage;
        mhp=mhp-(target.p_ar.second.protection)/4;
        target.get_damage(mhp);
        std::cout<<"Цель получила "<<mhp<<" урона"<<std::endl;
    }
    
    return mhp;
}
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
void Player::fatigue()
{
    hunger--;
    if (is_hungry())
        health--;
}
void Player::print_invetory()
{
    int i=0;
    while (i<f_bag.size()) {
        std::cout<<f_bag[i].count<<" "<<f_bag[i].name<<" ";
        i++;
    }
}
bool Player::healing(int count)
{
    int health1=health;
    if (health<100)
    {
    health+=count;
    health=health-(MAX_HEALTH*2)*(health/(MAX_HEALTH*2));
    health=health-(health-MAX_HEALTH);
    std::cout<<"Вы восстановили "<<health-health1<<" здоровья, теперь у вас "<<health<<" здоровья"<<std::endl;
    return true;
    }
    std::cout<<"У вас полное здоровье"<<std::endl;
    return false;
    
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

void Player::have_a_dinner(std::string name) //добавить уход веса
{
    int temp = hunger;
    for (int i=0;i<f_bag.size();i++)
        if (name==f_bag[i].name)
            {
                if (hunger<0 or health<100)
                {
                    hunger+=f_bag[i].satiety;
                    if (hunger>0)
                        hunger=0;
                    carrying+=f_bag[i].weight;
                    std::cout<<"Вы съели "<<f_bag[i].name <<" и восстановили "<<hunger-temp<<" голода, теперь ваш голод равен "<<hunger<<std::endl;
                    healing(f_bag[i].satiety/2);
                    f_bag[i].count--;
                    if (f_bag[i].count == 0)
                        f_bag.erase(f_bag.begin() + i);
                    return;
                }
            
            std::cout<<"Вы не голодны"<<std::endl;
            return;
            }
    else
        std::cout<<"У вас нет такого предмета в инвентаре"<<std::endl;
}

void Player::print_info()
{
    std::cout<<std::endl;
    std::cout<<"Класс: "<<clas<<std::endl;
    std::cout<<"Имя: "<<name<<std::endl;
    std::cout<<"Гендep: "<<gender<<std::endl;
    std::cout<<"Раса: "<<p_race<<std::endl;
    std::cout<<"Здоровье: "<<health<<std::endl;
    std::cout<<"Оружие: "<<p_ar.second.name<<std::endl;
    std::cout<<"Уровень: "<<level.level<<std::endl;
    std::cout<<"Прогресс уровня: "<<level.level_bar<<"/100"<<std::endl;
    std::cout<<"Деньги: "<<money<<std::endl;
    std::cout<<"Голод: "<<hunger<<std::endl;
    std::cout<<"Оружие: "<<p_ar.first.name<<std::endl;
    std::cout<<"Вес:  "<<carrying<<"/ "<<max_carrying<<std::endl;
    std::cout<<"Из еды у вас есть: "; print_invetory(); std::cout<<std::endl;
}
Player::~Player(){}
Enemy::~Enemy(){}
Unit::~Unit()
{

}
