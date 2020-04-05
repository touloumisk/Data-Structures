#include "btree1.h"
#include "foit.h"


void Load(fstream & , BTTableClass & );
void ReadLine(fstream & InputFile, KeyFieldType Word,
   LastName Definition,FirstName first,etos_spoudwn et,age xr);

const int LineMax = KeyFieldMax + lastnamemax+firstnamemax+agemax+etosmax;

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
   ReadLine(InputFile, Item.am,Item.last_name,Item.first_name,Item.etos,Item.xron);
   strcpy(Item.KeyField,Item.am);
  
  char  am[4];
  cout<<"Give AM of the entry to be deleted:";

  cin>>am;
  int index;
   int count = 0;
   foit *f = new foit();
    while (! InputFile.fail())
      {
   count++;
      cout<<Item.KeyField<<"_"<<Item.last_name<<"_"<<Item.first_name<<"_"<<Item.etos<<"_"<<Item.xron<<"_"<< endl;
      if (strcmp(am,Item.KeyField)) Table.Insert(Item);
      else {index = count;}
     
      
       ReadLine(InputFile, Item.am,Item.last_name,Item.first_name,Item.etos,Item.xron);
       
       strcpy(Item.KeyField,Item.am);
  
      }
      cout<<"CPOUNT="<<index;
      InputFile.seekg(count*sizeof(foit),ios::beg);
      InputFile.read(reinterpret_cast <char *> (&f), sizeof(foit));
      f->get_last();
      std::ifstream is ("eggrafes.txt", std::ifstream::binary);
      is.seekg ((index-1)*sizeof(foit), is.beg);
    int length = sizeof(foit);
    cout<<"Length="<<length<<endl;
    
     char * buffer = new char [length];
     //is.seekg (index-1, is.beg);
    // read data as a block:
    is.read (buffer,length);
    cout<<"HERE,";
     std::cout.write (buffer,length);
     
   }

   void ReadLine(fstream & InputFile, KeyFieldType Word,
   LastName Definition,FirstName first,etos_spoudwn et,age xr)
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
  
  while (pch != NULL)
  {
       
    if (count==2) last_len = strlen(pch); 
    if (count==3) first_len = strlen(pch);
    if (count==4) etos_len = strlen(pch);
    if (count==5) age_len = strlen(pch); 
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
   
   
  }
  
  int main()
  {
      CreatePrimaryIndex("eggrafes.txt","prim.dat");
      system("pause");
  }
