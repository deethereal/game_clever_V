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
std::map <std::string, Food> food_list={{"хлеб", Food(0,0,0)} };


Unit::Unit()
{
}
Enemy::Enemy()
{
}

Enemy::Enemy(std::string race1, int hp, int experience_, int power, std::string w_type, int arm, int deng , std::string type_drop, std::vector<std::string> drop_id_f, std::vector<int> f_count, std::vector<std::string> drop_id_w, std::vector<int> w_count, std::vector<std::string> drop_id_a, std::vector<int> a_count)
{
    money=deng;
    race = race1;
    MAX_HEALTH=hp;
    health = hp;
    experience=experience_;
    p_ar.first.strength=power;
    p_ar.first.type_of_dam=w_type;
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
            {
                e_inv.w_part.push_back(weapon.find(drop_id_w[i])->second);
                e_inv.w_part.back().count=w_count[i];
            }
        if (ar)
            for (int i=0;i<drop_id_a.size();i++)
            {
                e_inv.a_part.push_back(armory.find(drop_id_a[i])->second);
                e_inv.a_part.back().count=a_count[i];
            }
        if (fo)
             for (int i=0;i<drop_id_f.size();i++)
            {
                e_inv.f_part.push_back(food_list.find(drop_id_f[i])->second);
                e_inv.f_part.back().count=f_count[i];
            }
}
void Player::otladka_goloda()
{
    hunger-=20;
}
bool Enemy::hp_positive()
{
    if (health>0)
        return true;
    else
        return false;
}

inventory Enemy::E_is_alive(int g_damage, Player& p)
{
    inventory temp;
    if (health<=0)
    {
        std::cout<<"цель мертва"<<std::endl;
        p.level.level_bar+=experience;
        p.level.lvlup();
        p.level.progress(experience);
        if (race=="гуманоид" or race=="зверь" or race=="БОСС" or race=="нeжить")
        {
            std::cout<<"Из моба выпало"<<std::endl;
            temp=mob_drop();
        }
        this->~Enemy();

    }
    else
        std::cout<<"осталоcь "<<MAX_HEALTH-g_damage<<" здоровья"<<std::endl;
    return temp;
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
        std::cout<<races[i]<<" ";
    std::cout<<std::endl;
    std::string mb_race;
    int temp = -1;
    while (temp!=1)
    {
    std::cin>>mb_race;
    for(int i=0;i<8;i++)
        if (mb_race == races[i])
        {
            temp=1;
            break;
        }
    if (temp==-1)
        std::cout<<"Это не являтеся расой, выберите одну из предложенных"<<std::endl;
    }
    race=mb_race;
    if (race=="дракон")
        MAX_HEALTH=120; 
    else
        MAX_HEALTH=100;
    health=MAX_HEALTH;
    if (race=="дворф")
        armor=10;
    else
        armor=0;
    if (race=="гоблин")
        money = 50;
    if (race=="орк")
        physic_damage+=3;
    if (race=="эльф")
        magic_damage+=3;
    if (race=="троль")
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
    if (race=="каджит")
        add_food(food_list.find("хлеб")->second);
    add_food(food_list.find("хлеб")->second);
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
        return false;
    if (hunger<=-80)
        std::cout<<"Вы начинаете голодать"<<std::endl;
    std::cout<<"Вы голодны"<<std::endl;
    health-=10;
    return true;
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



void Player::fatigue()
{
    hunger--;
    is_hungry();
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


void Player::have_a_dinner(std::string name)
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
    std::cout<<"У вас нет такого предмета в инвентаре"<<std::endl;
}

void Player::print_info()
{
    std::cout<<std::endl;
    std::cout<<"Класс: "<<clas<<std::endl;
    std::cout<<"Имя: "<<name<<std::endl;
    std::cout<<"Гендep: "<<gender<<std::endl;
    std::cout<<"Раса: "<<race<<std::endl;
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
