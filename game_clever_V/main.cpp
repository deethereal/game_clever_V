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
//дописать E_is_alive
int main()
{
    std::cout<<"Добро пожаловать в игру M\\W\\C "<<std::endl;
    std::cout<<"Каждое действие стоит 1 еду (кроме еды)"<<std::endl<<"Когда у вас кончится еда, вы начнете получать по 10 урона в ход"<<std::endl;
    Player player;
    player.print_info();
    std::vector<std::string> test_list1 = {"bread"};
    std::vector<std::string> test_list2 = {"w_base"};
    Enemy test_mob("гуманоид", 55, 32,10,20, "f", test_list1);
    std::string command="";
    while (command!="end" and player.is_alive())
    {
        std::cin>>command;
        if (command=="healing")
        {
            if(player.healing(player.pray(0)))
                player.fatigue();
        }
        else if (command =="хлеб")
                player.have_a_dinner(command);
        else if (command == "выкинуть")
            player.drop_food("хлеб");
        else if (command == "info")
            player.print_info();
        else if (command=="fight")
        {
            test_mob.E_is_alive(player.damage(test_mob, player));
        }
        else if (command=="хп")
        {
            player.get_damage(20);
        }
        else
            std::cout<<"Такой команды нет, введите другую"<<std::endl;
    }
    return 0;
}
