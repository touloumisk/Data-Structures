#include "btree1.h"


int main()
{
    ItemType Item;
    cout<<"Give Data for the student to be inserted into index:"<<endl;
    cout<<"Give AM:";
    cin>>Item.am;
    cout<<endl;
    
    cout<<"Give Last Name:";
    cin>>Item.last_name;
    cout<<endl;
    
    cout<<"Give First Name:";
    cin>>Item.first_name;
    cout<<endl;
    
    cout<<"Give Etos:";
    cin>>Item.etos;
    cout<<endl;
    
    cout<<"Give Age:";
    cin>>Item.xron;
    cout<<endl;
    
    strcpy(Item.KeyField,Item.am);
    
 BTTableClass BTTable('a', "prim.dat");   
 cout<<BTTable.Get_NumNodes()<<endl;
 BTTable.Insert(Item);
 
 cout<<Item.KeyField<<"_"<<Item.last_name<<"_"<<Item.first_name<<"_"<<Item.etos<<"_"<<Item.xron<<"_"<< endl;
   //   Table.Insert(Item);
      
      system("pause");
}
