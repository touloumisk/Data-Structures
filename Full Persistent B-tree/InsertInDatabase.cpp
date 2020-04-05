#include "foit.h"
#include "fstream"
void InsertInDatabase(foit *x,std::string FileName)
{
     bool ex=false;
     int am,etos,age;
     string first,last ;
     char ch;
     int count =0;
 	 ifstream iFile(FileName.c_str(),ios::in);
     
     if (!iFile){
                cerr<<"file could not be opened";
                exit(1);
                }

	iFile.close();
	ofstream out(FileName.c_str(),ios::out | std::ios::app);
	out.seekp(ios::end);
	if (!ex){ 
              cout<<" EISAGWGH EGGRAFHS ME AM "<<x->getAM()<<" STO ARXEIO EGGRAFHS"<<endl; 
              out<<x;
              }
	else cout<<"LATHOS DIPLO EGGRAFH"<<endl;
	
}

int main()
{
int am,etos,age;
      string first,last ;
	   foit *f=new foit();
	   
       cout<<"Dwse AM:";
       cin>>am;
       f->setAM(am);
       cout<<"\nDwse last name:";
       cin>>last;
       f->set_last(last);
       cout<<"\nDwse first:";
       cin>>first;
       f->set_first(first);
       cout<<"\nDwse etos spoudwn:";
       cin>>etos;
       f->set_etos(etos);
       cout<<"\nDwse age:";
       cin>>age;
       f->set_age(age);
	   
	   InsertInDatabase(f,"eggrafes.txt");
	   
	   system("pause");
	}
