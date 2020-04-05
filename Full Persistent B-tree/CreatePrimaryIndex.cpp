#include "btree1.h"

void Load(fstream & , BTTableClass & );
void ReadLine(fstream & InputFile, KeyFieldType Word,
   LastName Definition,FirstName first,etos_spoudwn et,age xr, Version ver, char &OP);

const int LineMax = KeyFieldMax + lastnamemax+firstnamemax+agemax+etosmax+vmax;

typedef char StringType[LineMax];


bool CreatePrimaryIndex(char * f,char * filename)
{
   fstream Source;
   BTTableClass BTTable('w', filename);

   Source.open(f, ios::in);
   if (Source.fail())
      {
                       
      cerr << "ERROR: Unable to open file btree.txt" << endl;
    
      exit(1);
      }

   Load(Source, BTTable);

   Source.close();
 }
 
 void Load(fstream & InputFile, BTTableClass & Table)
   {
   ItemType Item;
   int Count;

   Count = 0;
   ReadLine(InputFile, Item.am,Item.last_name,Item.first_name,Item.etos,Item.xron,Item.ver, Item.OP);
   strcpy(Item.KeyField,Item.am);
  
   
    while (! InputFile.fail())
      {
      
      cout<<Item.KeyField<<"_"<<Item.last_name<<"_"<<Item.first_name<<"_"<<Item.etos<<"_"<<Item.xron<<"_"<<Item.ver<<"_"<<Item.OP<<"_"<<endl;
    //  Item.count=0;
    //
      Table.Insert(Item);

     
      
      
       ReadLine(InputFile, Item.am,Item.last_name,Item.first_name,Item.etos,Item.xron,Item.ver,Item.OP);
       strcpy(Item.KeyField,Item.am);
  
      }
   }

   void ReadLine(fstream & InputFile, KeyFieldType Word,
   LastName Definition,FirstName first,etos_spoudwn et,age xr, Version ver, char &OP)
   {
   char Line[LineMax];
   int k, ch;

   InputFile.getline(Line, LineMax);   // will read the newline char
   if(strcmp(Line,"")==0) return;
   char * pch;
   pch = strtok (Line,",");
  
  int count = 1;
  int last_len;
  int first_len;
  int etos_len;
  int age_len;
  int ver_len;
  
  while (pch != NULL)
  {
       
    if (count==2) last_len = strlen(pch); 
    if (count==3) first_len = strlen(pch);
    if (count==4) etos_len = strlen(pch);
    if (count==5) age_len = strlen(pch); 
    if (count==6) ver_len = strlen(pch);
    pch = strtok (NULL, ",");
    count++;
  }

   for (k = 0; k < AMMax; k++)
      Word[k] = Line[k];
   Word[AMMax] = NULLCHAR;

  int j=0;
 
   for (k = 0; k < last_len; k++)
      {
      ch = Line[AMMax + k+1];
      if (ch == '\n' || ch=='\t')
         break;
      if (ch!=' '){Definition[j] = ch; j++;}
      }
   
   Definition[j] = NULLCHAR;
  
  int r=0;
  char cht;
   for (k = 0; k < first_len; k++)
      {
      cht = Line[AMMax + last_len + k+2];
     
      if (cht == '\n' ||cht=='\t' )
         break;
      if(cht!=' '){first[r] = cht; r++;}
      }
   first[r] = NULLCHAR;
  
   int y=0;
    for (k = 0; k < etos_len; k++)
      {
      ch = Line[AMMax + first_len+last_len + k+3];
   
      if (ch == '\n' ||ch=='\t' )
         break;
      if (ch!=' '){et[y] = ch;y++;}
      }
   et[y] = NULLCHAR;
   
   int z=0;
   for (k = 0; k < age_len; k++)
      {
      ch = Line[AMMax + last_len+first_len+etos_len + k+4];
   
      if (ch == '\n' ||ch=='\t' )
         break;
      if (ch!=' '){xr[z] = ch;z++;}
      }
   xr[j] = NULLCHAR;
   
   int p=0;
   for (k = 0; k < age_len; k++)
      {
      ch = Line[AMMax + last_len+first_len+etos_len + k+7];
   
      if (ch == '\n' ||ch=='\t' )
         break;
      if (ch!=' '){ver[p] = ch;p++;}
      }
   ver[j] = NULLCHAR;
   
   p=0;
   char op;
    for (k = 0; k < 1; k++)
      {
      ch = Line[AMMax + last_len+first_len+etos_len + k+9];
   
      if (ch == '\n' ||ch=='\t' )
         break;
      if (ch!=' '){OP = ch;}
      }
   //ver[j] = NULLCHAR;
 
  }
  
  int main()
  {
      CreatePrimaryIndex("eggrafes.txt","prim.dat");
      system("pause");
  }
