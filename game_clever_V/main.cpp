//
//  main.cpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//1

#include <iostream>
#include "units.h"
#include <typeinfo>
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
//дописать E_is_alive, сделать дроп вещей
int main()
{
    std::cout<<"Добро пожаловать в игру M\\W\\C "<<std::endl;
    std::cout<<"Каждое действие стоит 1 еду (кроме еды)"<<std::endl<<"Когда у вас кончится еда, вы начнете получать по 10 урона в ход"<<std::endl;
    Player player;
    player.print_info();
    std::vector<std::string> test_list1 = {"bread"};
    std::vector<std::string> test_list2 = {"w_base"};
    Enemy test_mob("гуманоид", 55,32,10,20, "f", test_list1);
    std::string command="";
    std::cout<<std::endl;
    while (command!="end" and player.is_alive())
    {
        std::cin>>command;
        if (command=="healing")
        {
            if(player.healing(player.pray(0)))
                player.fatigue();
        }
        else if (command =="поесть")
        {
            std::cout<<"что вы хотите съесть?"<<std::endl;
            player.print_invetory();
            std::string snack;
            std::cin>>snack;
            player.have_a_dinner(snack);
        }
        else if (command == "выкинуть")
            player.drop_food("хлеб");
        else if (command == "info")
            player.print_info();
        else if (command=="fight" ) ///пофиксить
        {
            if (test_mob.hp_positive())
            {
                inventory mob_drop = test_mob.E_is_alive(player.damage(test_mob, player));
                if (mob_drop.is_empty()!=0)
                {
                    std::cout<<"цель мертва"<<std::endl;
                    mob_drop.show();
                    std::cout<<"Введите название вещей и количество, которое хотите взять(вещь-количество, и т.д.(не советую обманывать))"<<std::endl;
                    std::string input;
                    std::cin>>input;
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

                    
                    }
                    //проверка на читерство кончилась
                    if (not cheat)
                        player.take_items( player.create_inv(inv));
                    //дописать повтор,  пока не закончит класть
                }
                player.fatigue();
            }
            else
                std::cout<<"Врагов вокруг нет"<<std::endl;
        }
        else if (command=="хп")
        {
            player.get_damage(20);
        }
        else if (command=="голод")
            player.otladka_goloda();
        else
            std::cout<<"Такой команды нет, введите другую"<<std::endl;
    }
    
    return 0;
}
