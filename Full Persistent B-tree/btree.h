
#ifndef BTREE_H
#define BTREE_H
#include "table.h"




const int MaxKeys = 11;   // max number of keys in a node

const int MaxKeysPlusOne = MaxKeys + 1;

const int MinKeys = 5;    // min number of keys in a node

const long NilPtr = -1L;   // the L indicates a long int


typedef struct
   {
   int Count;               // Number of keys stored in the current node
   ItemType Key[MaxKeys];   // Warning: indexing starts at 0, not 1
   long Branch[MaxKeysPlusOne];   // Fake pointers to child nodes
   int Id;
   } NodeType;


void Error(char * msg);


class BTTableClass: public TableBaseClass
   {
   public:
      BTTableClass(char Mode, char * FileName);
      ~BTTableClass(void);
      bool Empty(void) const;
      bool Insert(ItemType & Item);
      bool Delete(KeyFieldType SearchKey);
      bool Retrieve(KeyFieldType SearchKey, ItemType & Item);
      void Dump(void);   // for debugging only - could be removed
      void FindRange(KeyFieldType k1,KeyFieldType k2,char *index);
      void Check(void);   // for debugging only
      long Get_NumNodes(){return NumNodes;}
   private:
      void CheckSubtree(long Current, KeyFieldType & Last); // for debugging
      bool SearchNode(KeyFieldType Target, int & location,ItemType &z ) ;
      void AddItem(const ItemType & NewItem, long NewRight,
         NodeType & Node, int Location);
      void Split(const ItemType & CurrentItem, long CurrentRight,
         long CurrentRoot, int Location, ItemType & NewItem,
         long & NewRight);
      void PushDown( ItemType & , long , bool & , ItemType & , long & );
      long Root;       // fake pointer to the root node
      long NumNodes;   // number of nodes in the B-tree
      int NodeSize;    // number of bytes per node
      NodeType CurrentNode;   // storage for current node being worked on
     // static int CurrentIndex;
   };
#endif
