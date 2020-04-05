#include "foit.h"
#include "fstream"
bool CreateDatabase(string );
int main()
{ 
     int am,etos,age;
      string first,last ;
      
    cout<<CreateDatabase("eggrafes.txt");
  
    system("pause");
}   

bool CreateDatabase(std::string FileName)
{
     int am,etos,age;
      string first,last ;
     char ch;
     ofstream File(FileName.c_str(),std::ios::out);
     File.clear();
     
     am = 1000;
     if ( !File ) {
 cerr << "File could not be opened." << endl;
     exit( 1 );
    
     } // end if

    
 



     if (!File){
                cerr<<"file coud not be opened";
               // exit(1);
                }
     else 
     {   
         
        while(am<9997)
        {        
        foit *f=new foit();       
       f->setAM(am);
       last = "Touloumis";
       f->set_last(last);
       first = "Kostas";
       f->set_first(first);
       etos = 5;
       f->set_etos(etos);
       age= 22;
       f->set_age(age);
           
       File<<f;
       am++;
       }
     }             
                
}
