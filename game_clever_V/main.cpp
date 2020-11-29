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
#include <cstdlib>

using namespace std;
bool e_killed[1]={false};

//дописать E_is_alive, сделать дроп вещей
int main()
{
   
    srand(4224);
    std::cout<<"Добро пожаловать в игру M\\W\\C "<<std::endl;
    std::cout<<"Каждое действие стоит 1 еду (кроме еды)"<<std::endl<<"Когда у вас кончится еда, вы начнете получать по 10 урона в ход"<<std::endl;
    Player player;
    player.print_info();
    std::string command="";
    std::cout<<std::endl;
    std::cout<<"В любой момент вы можете ввести \"info\", чтобы узнать информацию о вашем персонаже\n";
    
    std::cout<<"Вы просыпаетесь без памяти, единтсвенное, что вы помните, что вам надо найти \"Амулет Счастья\" и имя \"Тенурион\". \n Вы находите местного жителя, и он рассказывает вам легенду о Тенурионе, который носит тот самый Амулет, указывает направление.\nВы готовы отправиться в путь? y/n \n";
    std::string answer="info";
    while (answer=="info")
    {
    std::cin>>answer;
    if (answer=="y")
        std::cout<<"Я всегда знал, что ты смелый\n";
    else if (answer=="info")
        player.print_info();
    else
        std::cout<<"Это был риторический вопрос\n";
    }
    std::cout<<"День первый\n";
    //написать лор
    std::cout<<"На пути вы встречаете маленькомго монстра, похожего на гнома, у него 60 здоровья, 15 атаки и 20 брони, хотите с ним драться? y/n\n";
    std::cin>>answer;
    if (answer=="y")
    {
        //std::vector<std::string> gnom_f={"хлеб"};
        //std::vector<int> gnom_f_count={10};
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
    
    
    cout<<"END";
    
    
    
    
    
    
    
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
