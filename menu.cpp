#include "menu.h"
#include <conio.h>
#include <windows.h>
#include <map>

Menu::Menu(){
    system("title Password-Manager");
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
    std::cout<<"1.Add entry\n\n2.Remove Entry\n\n3.Change Entry\n\n4.See all entries\n\n5.See entries , sorted by tags\n\n6.See entries by tag\n\n7.Exit\n\nOption : ";
    std::cin>>aux;
    if(aux<1 || aux>7)
        return -1;
    return aux;
}

void Menu::handle(){
    while(1){
        int option=display();
        while(option == -1)
            option=display();
        std::cin.ignore();
        opt1:
        if(option==1){
            std::string usr,pswd,url,tag;
            char ch;
            int tags=0;
            system("cls");
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
            std::string url,user;
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Url : ";
            std::getline(std::cin,url);
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Username : ";
            std::getline(std::cin,user);
            mng.remove_entry(Entry(user,"",url));
            refresh();
        }
        if(option==3){
            std::string url,user;
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Url : ";
            std::getline(std::cin,url);
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Username : ";
            std::getline(std::cin,user);
            mng.remove_entry(Entry(user,"",url));
            option=1;
            goto opt1;
        }
        if(option==4){
            int nr=0;
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            for(int i=0;i<mng.entries().size();i++){
                std::cout<<"Entry # "<<i+1<<std::endl;
                std::cout<<"\tUsername : "<<mng.entries()[i].username()<<std::endl<<"\tPassword : "<<mng.entries()[i].password();
                std::cout<<std::endl<<"\tUrl : "<<mng.entries()[i].url()<<'\n';
            }
            std::cout<<"Press any keys to continue";
            _getch();
        }
        if(option==5){
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::map<std::string,std::vector<Entry> >mp;
            for(int i=0;i<mng.entries().size();i++){
                if(mng.entries()[i].tags().size()==0)
                    mp[""].push_back(mng.entries()[i]);
                for(int j=0;j<mng.entries()[i].tags().size();j++)
                    mp[mng.entries()[i].tags()[j]].push_back(mng.entries()[i]);
            }
            for(auto it:mp){
                std::cout<<'\n'<<"TAG : "<<it.first<<'\n';
                for(auto aux:it.second){
                    std::cout<<"\tUsername : "<<aux.username()<<'\n';
                    std::cout<<"\tPassword : "<<aux.password()<<'\n';
                    std::cout<<"\tUrl : "<<aux.url()<<'\n'<<'\n';
                }
            }
            std::cout<<"Press any keys to continue";
            _getch();
        }
        if(option==6){
            std::string tag;
            system("cls");
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"Enter tag name : ";
            std::getline(std::cin,tag);
            if(tag==""){
                system("cls");
                option=4;
                goto opt1;
            }
            std::cout<<std::string(50,' ')<<"|Password Manager|"<<std::string(3,'\n');
            std::cout<<"TAG : "<<tag<<'\n'<<'\n';
            for(auto it:mng.entries())
                for(auto it2:it.tags())
                    if(it2==tag){
                        std::cout<<"\tUsername : "<<it.username()<<'\n';
                        std::cout<<"\tPassword : "<<it.password()<<'\n';
                        std::cout<<"\tUrl : "<<it.url()<<'\n'<<'\n';
                    }
            std::cout<<"Press any keys to continue";
            _getch();
        }
        if(option==7){
            refresh();
            exit(0);
        }
    }
}
