//
//  units.h
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
// проверяю, что все работает(1)6

#ifndef units_h
#define units_h
#include "items.hpp"


struct level
{
    int level;
    int level_bar;
    bool is_new=false;
    void lvlup()
    {
        if (level_bar>=100)
        {
            level++;
            is_new=true;
            level_bar-=100;
        }
    }
    void progress(int count){
        std::cout<<"Вы получили "<<count<<" опыта"<<std::endl;
        std::cout<<"Ваш текущий уровень: "<<level<<std::endl;
        std::cout<<"До следующего уровня: "<<level_bar<<"/100"<<std::endl;
    }
};

struct inventory
{
    std::vector<Food> f_part;
    std::vector<Armor> a_part;
    std::vector<Weapon> w_part;
    void show()
    {
        int i=0;
        std::cout<<"Из еды у него было: "<<std::endl;
        while (i<f_part.size()) {
            std::cout<<f_part[i].count<<" "<<f_part[i].name<<" ";
            i++;
        }
        std::cout<<"\n";
        i=0;
        std::cout<<"Из оружия у него было: "<<std::endl;
        while (i<w_part.size()) {
            std::cout<<w_part[i].count<<" "<<w_part[i].name<<" ";
            i++;
        }
        std::cout<<"\n";
        i=0;
        std::cout<<"Из снаряжения у него было: "<<std::endl;
        while (i<a_part.size()) {
            std::cout<<a_part[i].count<<" "<<a_part[i].name<<" ";
            i++;
        }
        std::cout<<"\n";
    }
    void show_for_selling()
    {
        int i=0;
        std::cout<<"Из еды : "<<std::endl;
        while (i<f_part.size()) {
            std::cout<<f_part[i].count<<" "<<f_part[i].name<<" за "<<f_part[i].cost<<" монет каждый\n";
            i++;
        }
        i=0;
        std::cout<<"Из оружия : "<<std::endl;
        while (i<w_part.size()) {
            std::cout<<w_part[i].count<<" "<<w_part[i].name<<" за "<<w_part[i].cost<<" монет каждый\n";
            i++;
        }
        std::cout<<"\n";
        i=0;
        std::cout<<"Из снаряжения: "<<std::endl;
        while (i<a_part.size()) {
            std::cout<<a_part[i].count<<" "<<a_part[i].name<<" за "<<a_part[i].cost<<" монет каждый\n";
            i++;
        }
        std::cout<<"\n";
    }
    unsigned long is_empty()
    {
        return f_part.size()+a_part.size()+w_part.size();
    }
};

void delete_it(inventory& from, inventory what);

class Unit
{
protected:
    std::string gender;
    std::string name;
    std::string race;
    std::string races[8] = {"орк", "эльф", "человек", "дворф", "тролль", "гоблин", "драконоид", "каджит"};
    int health;
    int MAX_HEALTH;
    int armor;
    float money=0;
    int mana;
    int MAX_MANA;
    int magic_damage=20;
    int physic_damage=0;
    std::pair<Weapon, Armor> p_ar;
  
public:
    inventory create_inv(std::vector<std::pair<std::string, int>> items_list);
    void money_increase(float value);
    void money_decrease(float value);
    float return_money();
    void get_damage(int damage);
    int damage(Unit& target, Unit& attacker);
    bool is_p=false;
    std::string clas;
    Unit();
    
    ~Unit();
};
class Player : public Unit
{
protected:
    int carrying;
    int max_carrying;
    float p_mult=0;
    int hunger;
    
    bool add_item(Armory item);
    bool add_food(Food snack);
   

    
public:
    Player();
    std::vector<Armory> a_bag;
    std::vector <Food> f_bag;
    level level;
    void prival();
    void show_ar(bool selling=false);
    void equip(std::string thing);
    void print_invetory(bool selling=false);
    void fatigue();
    void show_inv(bool selling=false);
    void otladka_goloda();
    void print_info();
    bool is_alive();
    bool is_hungry();
    void level_up();
    void drop_food(std::string name);
    void have_a_dinner(std::string name);
    bool take_items(inventory from);
    void delete_part(inventory what);
    bool healing(int count);
    int pray(int target);  //target = 1, если враг,target= 0, если персонаж
    ~Player();
    
};
class fNPC: public Unit
{
protected:
    inventory npc_inv;
public:
    fNPC();
    fNPC(int value, std::string type_drop="", float coef=2,std::vector<std::string> drop_id_f={"1"}, std::vector<int> f_count={1}, std::vector<int> f_cost={1}, std::vector<std::string> drop_id_w={"1"}, std::vector<int> w_count={1}, std::vector<int> w_cost={1},
         std::vector<std::string> drop_id_a={"1"}, std::vector<int> a_count={1}, std::vector<int> a_cost={1});
    void sell(Player& p);
    float mult;
    void add_items(inventory bag);
    ~fNPC();
    
};
class Enemy: public Unit
{
protected:
    //std::string notp_race[6]={"гуманоид", "паук", "зверь", "чудище", "БОСС","нежить"};
    inventory e_inv;
    int experience;
    inventory mob_drop();
public:
    Enemy();
    Enemy(std::string race1, int hp, int experience_, int power, std::string w_type, int arm, int deng=0, std::string type_drop="", std::vector<std::string> drop_id_f={"1"}, std::vector<int> f_count={1}, std::vector<std::string> drop_id_w={"1"}, std::vector<int> w_count={1},
        std::vector<std::string> drop_id_a={"1"}, std::vector<int> a_count={1});
    inventory E_is_alive(int g_damage,Player& p, int i);
    void e_attack(Player& p, Enemy& e);
    bool hp_positive();
    ~Enemy();
};
void p_attack(Enemy& target, Player& p,int i);
void fight_pve(Player& p, Enemy& u,int i);
void sell_to_npc(fNPC& seller, Player& p);
#endif /* units_h */
