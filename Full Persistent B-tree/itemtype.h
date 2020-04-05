
#ifndef ITEMTYPE_H
#define ITEMTYPE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


const int KeyFieldMax = 15;

const int AMMax = 4;

const int KFMaxPlus1 = KeyFieldMax + 1;

const int DataFieldMax = 36;

const int DFMaxPlus1 = DataFieldMax + 1;

const int lastnamemax = 15;

const int firstnamemax=15;

const int etosmax=3;

const int agemax = 4;

const int vmax = 3;

const int NULLCHAR = '\0';  // NULL character used to mark end of a string


typedef char KeyFieldType[KFMaxPlus1];

typedef char DataFieldType[DFMaxPlus1];

typedef char LastName[lastnamemax+1];

typedef char FirstName[firstnamemax+1];

typedef char etos_spoudwn[etosmax+1];

typedef char age[agemax+1];

typedef char AM[AMMax+1];

typedef char Version[vmax+1];
class ItemType
   {
           
   public:
   //int count;
   KeyFieldType KeyField;
   vector<int> v; 
   AM am;
   LastName last_name;
   FirstName first_name;
   etos_spoudwn etos;
   age xron;
   Version ver;
   int ins[5];
   int del[5];
   char OP;
   DataFieldType DataField;
 
   } ;
#endif
