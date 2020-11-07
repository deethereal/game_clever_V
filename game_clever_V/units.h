//
//  units.h
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//
#include "items.hpp"
#include <vector>
#ifndef units_h
#define units_h
struct level
{
    int level;
    int level_bar;
    void lvlup()
    {
        if (level_bar>=100)
        {
            level++;
            level_bar-=100;
        }
    }
};


class Unit
{
protected:
    std::string gender;
    std::string name;
    std::string p_race;
    std::string race[8] = {"орк", "эльф", "человек", "дворф", "тролль", "гоблин", "дракор", "каджит"};
    int health;
    int MAX_HEALTH;
    int armor;
    int money=0;
    int mana;
    int MAX_MANA;
    int magic_damage=20;
    int physic_damage=0;
    std::pair<Weapon, Armor> p_ar;
    level level;
public:
    void get_damage(int damage);
    void damage(Unit target, Unit attacker);
    std::string clas;
    Unit();
    int pray();
    
    ~Unit();
};
class Player : public Unit
{
protected:
    int carrying;
    int max_carrying;
    float p_mult=0;
    int hunger;
    void print_invetory();
    void add_item(Armory item);
    void add_food(Food snack);
    Armor p_armor;
    Weapon p_weapon;
    std::vector<Armory> a_bag;
    std::vector <Food> f_bag;
    
public:
    Player();
    void fatigue();
    void print_info();
    bool is_alive();
    bool is_hungry();
    void drop_food(std::string name);
    void have_a_dinner(std::string name);
    bool healing(int count);
    int pray(int target);  //target = 1, если враг,target= 0, если персонаж
    ~Player();
    
};
class fNPC: public Unit
{
    
    
};
class Enemy: public Unit
{
protected:
    std::string notp_race[6]={"гуманоид", "паук", "зверь", "чудище", "БОСС","нежить"};
    std::string e_race;
    std::vector<Food> f_inv;
    std::vector<Armor> a_inv;
    std::vector<Weapon> w_inv;
    int experience;
public:
    Enemy();
    Enemy(std::string race, int hp, int experience_, std::string type_drop, std::vector<std::string> drop_id_f={"1"}, std::vector<std::string> drop_id_w={"1"}, std::vector<std::string> drop_id_a={"1"});
    void E_is_alive();
    ~Enemy();
};


#endif /* units_h */
