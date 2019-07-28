#include "menu.h"
#include <conio.h>
#include <windows.h>

Menu::Menu(){
    passwds.open("passwd.xnec3");
    init();
    passwds.close();
}

void Menu::init(){
    mng.clear();
    std::string user,password,url,tags,aux;
    int tagsx,i;
    while(std::getline(passwds,user)){
        if(user=="")
            break;
        passwds>>std::ws;
        std::getline(passwds,password);
        passwds>>std::ws;
        std::getline(passwds,url);
        passwds>>std::ws;
        std::getline(passwds,tags);
        std::cout<<"HERE:"<<'\n'<<'\n'<<user<<"\n"<<password<<"\n"<<url<<'\n';
        passwds>>std::ws;
        mng.add_entry(Entry(Criptor::decrypt(user),Criptor::decrypt(password),Criptor::decrypt(url)));
        tagsx=i=0;
        while(i<tags.size() && std::isdigit(tags[i]))
            tagsx=tagsx*10+tags[i++]-'0';
        i++;
        for(;i<tags.size();i++)
            if(tags[i]==' ')
                mng.entries().back().add_tag(aux),aux.clear();
            else
                aux.push_back(tags[i]);
        aux.clear();
    }
}

void Menu::refresh(){
    std::ostringstream oss;
    for(int i=0;i<mng.entries().size();i++){
        oss<<Criptor::encrypt(mng.entries()[i].username())<<'\n'<<Criptor::encrypt(mng.entries()[i].password())<<'\n'<<Criptor::encrypt(mng.entries()[i].url())<<'\n';
        oss<<mng.entries()[i].tags().size();
        if(mng.entries()[i].tags().size())
            oss<<" ";
        for(int j=0;j<mng.entries()[i].tags().size();j++)
            oss<<mng.entries()[i].tags()[j]<<" ";
        oss<<'\n';
    }
    mng.clear();
    new_passwds.open("passwd.xnec3");
    new_passwds<<oss.str();
    new_passwds.flush();
    new_passwds.close();
    passwds.open("passwd.xnec3");
    init();
    passwds.close();
}

int Menu::display(){
    int aux;
    system("cls");
    std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
    std::cout<<"1.Add entry\n\n2.Remove Entry\n\n3.Change Entry\n\n4.See all entries\n\n5.See entries , sorted by tags\n\n6.See entries by tag\n\nOption : ";
    std::cin>>aux;
    if(aux<1 || aux>6)
        return -1;
    return aux;
}

void Menu::handle(){
    while(1){
        int option=display();
        while(option == -1)
            option=display();
        if(option==1){
            std::string usr,pswd,url,tag;
            char ch;
            int tags=0;
            system("cls");
            std::cin.ignore();
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Username : ";
            std::getline(std::cin,usr);
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Password : ";
            do{
                ch= _getch();
                pswd.push_back(ch);
                if(ch==8)
                    pswd.erase(pswd.begin()+pswd.size()-1);
            }while(ch!=VK_RETURN);
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Url : ";
            std::getline(std::cin,url);
            if(!mng.add_entry(Entry(usr,pswd,url)))
                continue;
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Enter number of tags : ";
            std::cin>>tags;
            std::cin.ignore();
            for(int i=0;i<tags;i++){
                std::cout<<"\nTag # "<<i<<" : ";
                std::getline(std::cin,tag);
                mng.entries().back().add_tag(tag);
            }
            refresh();
        }
        if(option==2){

        }
    }
}
