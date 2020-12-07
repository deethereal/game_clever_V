//
//  main.cpp
//  game
//
//  Created by denis  on 15.10.2020.
//  Copyright © 2020 denis . All rights reserved.
//

#include <iostream>
#include "units.h"
#include <typeinfo>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

std::string PATH = "/Users/denis/Documents/stage_two/game_clever_V/game_clever_V/lor.txt";
std::ifstream lf(PATH);
void help()
{
    cout<<"Вы можете:\nполечиться\nnоесть\ninfo\nвыкинуть";
}
void print_s()
{
    string s;
    getline(lf,s);
    cout<<s<<"\n";
}
bool e_killed[1]={false};

int main()
{
   //new commits(1)
    srand(4224);
    //вступление
    print_s();
    print_s();
    print_s();
    Player player;
    player.print_info();
    std::string command="";
    std::cout<<std::endl;
    //класс
    print_s();
    //начало лора
    print_s();
    print_s();
    print_s();
    std::string answer="info";
    while (answer=="info")
    {
    std::cin>>answer;
    if (answer=="д")
        std::cout<<"Я всегда знал, что ты смелый\n";
    else if (answer=="info")
        player.print_info();
    else
        std::cout<<"Это был риторический вопрос\n";
    }
    std::cout<<"\nДень первый\n";
    
    print_s(); //предложение про гнома
    std::cin>>answer;
    if (answer=="д")
    {
        Enemy gnom("гуманоид", 60,99,15,"физ",20,15, "f", {"хлеб"}, {10});
        std::cout<<"Кто будет атаковать первым -- решит жребий: ";
        char jreb='9';
        while (jreb!='1' and jreb!='0')
        {
            std::cout<<"выберете 1 или 0\n";
            std::cin>>jreb;
            
        }
        if (rand()%2==(int(jreb)-'0'))
        {
            cout<<"\nВы атакуете первым!\n\n";
            fight_pve(player, gnom,0);
        }
        else
        {
            cout<<"\nВы атакуете вторым!\n\n";
            gnom.e_attack(player, gnom);//починить
            fight_pve(player, gnom,0);
        }
    }
    if (e_killed[0])
    {
        cout<<"Ну и задал ты этому гному\n ";
        
    }
    else
        cout<<"Как только гном увидел вас, то сразу же дал деру, вы даже не успели ничего понять\n";
    
    
    print_s();//привал
    while (command!="стоп")
        {
            std::cin>>command;
            if (command=="полечиться")
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
            else if (command =="/помощь")
                help();
            
        }
    cout<<"Вы закончили привал и ложитесь спать, завтра вам предстоит долгий-долгий день....\n\n\n....\n\n\n";
    cout<<"День второй\n\n";
    print_s();//зашли в город
    std::cin>>answer;
    if (answer=="д")
    {
        while (answer=="д")
        {
        fNPC torgash(100,{"f"},{"хлеб"},{100},{1});
        torgash.sell(player);
        
        }
    }
    //РЕАЛИЗОВАТЬ КЛАСС fNPC и функцию trade
    return 0;
}
