#include "btree1.h"


int main()
{
	KeyFieldType KeyField;
	cout<<"Give KeyField to be deleted:";
	cin>>KeyField;
	BTTableClass BTTable('a', "prim.dat"); 
	BTTable.Delete(KeyField);
	system("pause");
   
 }    
