

#include <cctype>
#include "btree1.h"
#include <cstdlib>

bool ReadKeyboard(KeyFieldType Word)
   {
   int k, ch;
   bool start;

   cin >> Word;
  
   }


int main()
   {
   ItemType Item;
   char *index,ans;
   KeyFieldType SearchKey;
   int ch;
   char *chp;
   cout<<"1. Ephemeral read"<<endl<<"2.Version Read:";
   cin>>ch;
   if (ch==1)
   chp = "prim.dat";
   else 
   chp = "sec.dat";
   
   
   BTTableClass BTTable('r', chp);
   BTTable.Dump();
   system("pause");

if (BTTable.Empty())         Error("Table is empty");
      
      cout << "Enter the word to be looked up (or 'exit' to quit): ";

      while (ReadKeyboard(SearchKey) && strcmp(SearchKey,"exit"))
      {
      
      if (BTTable.Retrieve(SearchKey, Item))
      {           
      cout << " FOUND   "<<endl;
      cout<<"Last Name:"<<Item.last_name<<endl;
      cout<<"First Name:"<<Item.first_name<<endl;
      cout<<"Etos:"<<Item.etos<<endl;
      cout<<"Age:"<<Item.xron<<endl;
      cout<<"Version:"<<Item.ver<<endl;
      cout<<"Inserted in versions: ";
      for (int i=0; i<5; i++)
          if (Item.ins[i]!=-1)
             cout<<Item.ins[i]<<",";
        
      cout<<"\nDeleted in versions: ";
      for (int i=0; i<5; i++)
          if (Item.del[i]!=-1)
             cout<<Item.del[i]<<",";  
      //Item.ins[0]<<","<<Item.ins[1]<<","<<Item.ins[2]<<endl;
 
      }
      else cout << " Not found" << endl;
      
      cout << endl << "Enter the word to be looked up (or 'exit' to quit): ";
      
      }
 
    
  
   }
