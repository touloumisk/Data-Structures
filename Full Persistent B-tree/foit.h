#ifndef FOITHTHS_H
#define FOITHTHS_H

#include <iostream>
#include <cstring>
#include <new>
#include <iomanip>

using namespace std;

class foit{
friend ostream &operator<<(ostream &output,const foit *f)
{     
        output<<f->AM;     
        output<<","<<f->last;
        output<<","<<f->first;
        output<<","<<f->etos;
        output<<","<<f->age<<endl;
} 
friend istream &operator>>(istream &input,foit *f)
{

       input>>f->AM;
  
       input>>f->last;
    
       input>>f->first;
     
       input>>f->etos;
     
       input>>f->age;
}                
public:
             
void setAM(int am){AM=am;}
void set_last(string str){last=str;}
void set_first(string str){first=str;}     
void set_etos(int year){etos=year;}
void set_age(int a){age=a;}

int getAM(){return AM;}
string get_last(){return last;}
string get_first(){return first;}
int get_etos(){return etos;}
int get_age(){return age;}

void print()
{
     cout<<"AM:"<<AM<<endl;
     cout<<"Last name:"<<last<<endl;
     cout<<"First name:"<<first<<endl;
     cout<<"etos:"<<etos<<endl;
     cout<<"age:"<<age<<endl;
}

private:
int AM;
string last;
string first;
int etos;
int age;

};


 
 
#endif
