/* Filename:  btree.cpp

   This file contains the implementation of the functions of the
   BTTableClass as set up in btree.h.
*/
#ifndef BTREE1_H
#define BTREE1_H
#include "btree.h"

#include <cstring>

/* Given:  msg   A message.
   Task:   To print msg and exit the program.
   Return: Nothing to the program, of course, but returns 1 to the
           operating system.
*/


void Error(char * msg)
   {
   cerr << msg << endl;
   exit(1);
   }


/* Given:   Nothing (other than the implicit BTTableClass object)
   Task:    To print out all info associated with the current table.
            Note that this is for debugging purposes.  This function
            could be removed once debugging is complete.
   Return:  Nothing.
*/



void BTTableClass::FindRange(KeyFieldType k1,KeyFieldType k2,char *index)
{
    
 int k;
   long p;

 

   for (p = 0; p <= NumNodes; p++)
      {
      if (p % 4 == 3)
         {
         cout << " Press ENTER";
         cin.get();
         }

      DataFile.seekg(p * NodeSize, ios::beg);
      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      if (p == 0)
         {
        
         }
      else
         {
         
         for (k = 0; k < CurrentNode.Count; k++)
            {    //////////////////////////////////////////
            
            if (strcmp(CurrentNode.Key[k].KeyField,k1)>0 && strcmp(CurrentNode.Key[k].KeyField,k2)<0) cout<<"Yparxei::"<<CurrentNode.Key[k].KeyField<<" "<<
            CurrentNode.Key[k].last_name<<" "<<  CurrentNode.Key[k].first_name<<" "<<CurrentNode.Key[k].etos<<" "<<CurrentNode.Key[k].xron<<endl;

            }
        
         cout << endl << endl;
         }
      }    
     
     
}
void BTTableClass::Dump(void)
   {
   int k;
   long p;

  

   for (p = 0; p <= NumNodes; p++)
      {
      if (p % 4 == 3)
         {
         cout << " Press ENTER";
         cin.get();
         }

      DataFile.seekg(p * NodeSize, ios::beg);
      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);
      
      if (p == 0)
         {
         cout << "Node 0 is not part of tree, contains this data:" << endl;
         cout << "   NumItems = " << CurrentNode.Branch[0] << endl;
         cout << "   NumNodes = " << CurrentNode.Branch[1] << endl;
         cout << "   Root = " << CurrentNode.Branch[2] << endl;
         }
      else
         {
         cout << "Dump of node number " << p <<",with Id = "<<CurrentNode.Id<< endl;
         cout << "   Count: " << CurrentNode.Count << endl;

         cout << "   Keys: ";
         for (k = 0; k < CurrentNode.Count; k++)
            cout << CurrentNode.Key[k].KeyField << " ";     //////////////////////////////////////////

         cout << endl << "   Branches: ";
         for (k = 0; k <= CurrentNode.Count; k++)
            cout << CurrentNode.Branch[k] << " ";
         cout << endl << endl;
         }
      }
   }


/* Given:   Nothing (other than the implicit BTTableClass object)
   Task:    To do an inorder traversal of the B-Tree looking for out of
            order items.
            Note that this is for debugging purposes.  This function
            could be removed once debugging is complete.
   Return:  Nothing.
*/
void BTTableClass::Check(void)
   {
   KeyFieldType Last;

   Last[0] = '*';
   Last[1] = NULLCHAR;
   CheckSubtree(Root, Last);
   }


/* Given:   The implicit BTTableClass object plus:
            Current   A pseudopointer to the root node of the subtree.
            Last      The Last key field value that was checked.
   Task:    To do an inorder traversal of the subtree rooted at the
            current node.  Each key field value is checked against Last
            to see if it is out of order relative to Last.  If so,
            debugging info is printed, including a complete dump of
            the B-tree.
            Note that this is for debugging purposes.  This function
            could be removed once debugging is complete.
   Return:  Last      Updated to hold the last key field value checked.
*/
void BTTableClass::CheckSubtree(long Current, KeyFieldType & Last)
   {
   NodeType Node;
   int k;

   if (Current == NilPtr)
      return;

   DataFile.seekg(Current * NodeSize, ios::beg);
   DataFile.read(reinterpret_cast <char *> (&Node), NodeSize);
   for (k = 0; k < Node.Count; k++)
      {
      CheckSubtree(Node.Branch[k], Last);
      if ((Last[0] != '*') && (strcmp(Last, Node.Key[k].KeyField) >= 0))
         {
         cout << "Check has found a problem in node " << Current <<
            " index " << k << " key " << Node.Key[k].KeyField << endl;
         Dump();
         exit(1);
         }
      strcpy(Last, Node.Key[k].KeyField);
      }
   CheckSubtree(Node.Branch[Node.Count], Last);
   }


/* Given:   Mode      A char(r or w) to indicate read or write mode.
            FileName  A char string holding the external filename.
   Task:    This is the constructor for a BTTableClass object.  If mode
            r is specified, it opens the table stored in the given file
            for reading.  If w is specified, it opens a new, empty table
            for writing (to the given file).  A new empty table contains
            a "dummy" node (node zero) that will be used to hold info
            about the whole table.
   Return:  Nothing directly, but the implicit object is created.
*/
BTTableClass::BTTableClass(char Mode, char * FileName)
   {
   #ifdef DEBUG
      cout << "BTTableClass constructor called" << endl;
   #endif

   string line;
   OpenMode = Mode;
   NodeSize = sizeof(NodeType);

   if (Mode == 'r' )
      {
      DataFile.open(FileName, ios::in | ios::binary);
      if (DataFile.fail())
         Error("File cannot be opened");

      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);
      if (DataFile.fail())
         {   // assume the Btree is empty if you cannot read from the file
         NumItems = 0;
         NumNodes = 0;
         Root = NilPtr;
         }
      else   // Node zero is not a normal node, it contains the following:
         {
         NumItems = CurrentNode.Branch[0];
         NumNodes = CurrentNode.Branch[1];
         Root = CurrentNode.Branch[2];
         
        
         ifstream myfile ("pointers.txt");
         if (myfile.is_open())
         {
         getline (myfile,line) ; 
         char * pch;
         char* p = new char[line.length()+1];
         memcpy(p, line.c_str(), line.length()+1);
         pch = strtok (p,",");
         int count = 1;
         while (pch != NULL)
         {
         int value = atoi(pch);
         if (count==1) NumNodes = value;
         else if (count==2) NumItems = value;
         else if (count==3) Root = value;
         pch = strtok (NULL, " ,.-");
         count++;
         }
     
         myfile.close();
         }
         
         }//end else
      #ifdef DEBUG
         cout << "R";
      #endif
      }
      else if ( Mode =='a')
      {
        DataFile.open(FileName, ios::in | ios::out|ios::binary);
      if (DataFile.fail())
         Error("File cannot be opened");   
           
           DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);
      if (DataFile.fail())
         {   // assume the Btree is empty if you cannot read from the file
         NumItems = 0;
         NumNodes = 0;
         Root = NilPtr;
         }
      else   // Node zero is not a normal node, it contains the following:
         {
         NumItems = CurrentNode.Branch[0];
         NumNodes = CurrentNode.Branch[1];
         Root = CurrentNode.Branch[2];
         
         
     
          string line;
         ifstream myfile ("pointers.txt");
         if (myfile.is_open())
         {
         getline (myfile,line) ; 
         cout <<"l"<< line << '\n';
         
         char * pch;
         char* p = new char[line.length()+1];
         memcpy(p, line.c_str(), line.length()+1);
         pch = strtok (p,",");
         int count = 1;
         while (pch != NULL)
         {
         
         int value = atoi(pch);
       
         if (count==1) NumNodes = value;
         else if (count==2) NumItems = value;
         else if (count==3) Root = value;
         pch = strtok (NULL, " ,.-");
         count++;
         }
         
         myfile.close();
         }

         
         
         }
      }
   else if (Mode == 'w')
      {
      DataFile.open(FileName, ios::in | ios::out | ios:: trunc |
         ios::binary);
      if (DataFile.fail())
         Error("File cannot be opened");

      Root = NilPtr;
      NumItems = 0;
      NumNodes = 0;   // number does not include the special node zero
      CurrentNode.Branch[0] = NumItems;
      CurrentNode.Branch[1] = NumNodes;
      CurrentNode.Branch[2] = Root;
      DataFile.seekp(0, ios::beg);
      DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "W";
      #endif
      }

   else
      Error("Incorrect mode given to BTTableClass constructor");
   }


/* Given:   Nothing (other than the implicit object).
   Task:    This is the destructor for a BTTableClass object.  Its job
            is to destroy the BTTableClass object, while making sure that
            all of the table data is stored in the associated file.
   Return:  Nothing directly, but the file is updated.
*/
BTTableClass::~BTTableClass(void)
   {
   
   #ifdef DEBUG
      cout << endl << "BTTableClass destructor called" << endl;
   #endif
   
   char buffer [33];
   itoa (NumNodes,buffer,10);
   //NumNodes,NumItems,Root
   ofstream myfile;
  myfile.open ("pointers.txt");
  myfile << buffer<<",";
  
  itoa (NumItems,buffer,10);
  myfile << buffer<<",";
  
  itoa (Root,buffer,10);
  myfile << buffer<<",";
  
  myfile.close();
   
   
   if (OpenMode == 'w')
      {
      //  Be sure to write out the updated node zero:
      CurrentNode.Branch[0] = NumItems;
      CurrentNode.Branch[1] = NumNodes;
      CurrentNode.Branch[2] = Root;
      DataFile.seekp(0, ios::beg);
      DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "W";
      #endif
      }

   #ifdef DEBUG
      Dump();
   #endif

   DataFile.close();
   }


/* Given:   Nothing (other than the implicit object).
   Task:    To decide if the implicit table object is empty.
   Return:  In the function name, true if the table object is empty,
            false otherwise.
*/
bool BTTableClass::Empty(void) const
   {   // we could read node zero, but this is faster:
   return (Root == NilPtr);
   }


/* Given:   The implicit BTTableClass object as well as:
            Target        The value to look for in the CurrentNode field.
   Task:    To look for Target as a key in CurrentNode.
   Return:  In the function name, return true if found, false otherwise.
            Location      The index of where Target was found.  If not
                          found, index and index + 1 are the indices between
                          which Target would fit.  (If Target fits to the
                          left of the first key, returns index of -1.)
*/
bool BTTableClass::SearchNode( KeyFieldType Target,
   int & Location, ItemType & CurrentItem) 
   {
   bool Found;

   Found = false;
   if (strcmp(Target, CurrentNode.Key[0].KeyField) < 0)
      Location = -1;
   else
      { // do a sequential search, right to left:
          
      Location = CurrentNode.Count - 1;
      while ((strcmp(Target, CurrentNode.Key[Location].KeyField) < 0)
         && (Location > 0))
         Location--;

      if (strcmp(Target, CurrentNode.Key[Location].KeyField) == 0) Found = true;
        
         
      }

   return Found;
   }


/* Given:   The implicit BTTableClass object as well as:
            NewItem       Item to add to Node.
            NewRight      Pseudopointer to right subtree below NewItem.
            Node          The node to be added to.
            Location      The index at which to add newItem.
   Task:    To add Item to Node at index Location, and add NewRight
            as the branch just to the right of NewItem.  The addition is
            made by moving the needed keys and branches right by 1 in order
            to clear out index Location for NewItem.
   Return:  Node          Updated node.
*/
void BTTableClass::AddItem(const ItemType & NewItem, long NewRight,
   NodeType & Node, int Location)
   {
   int j;

   for (j = Node.Count; j > Location; j--)
      {
      Node.Key[j] = Node.Key[j - 1];
      Node.Branch[j + 1] = Node.Branch[j];
      }

   Node.Key[Location] = NewItem;
   Node.Branch[Location + 1] = NewRight;
   Node.Count++;
   }


/* Given: The implicit BTTableClass object as well as:
          CurrentItem    Item whose attempted placement into a node is
                         causing the node to be split.
          CurrentRight   Pseudopointer to the child just to the right of
                         CurrentItem.
          CurrentRoot    Pseudopointer to the node to be split.
          Location       Index of where CurrentItem should go in this node.
  Task:   To split the node that CurrentRoot points to into 2 nodes,
          pointed to by CurrentRoot and NewRight.  CurrentItem is properly
          placed in 1 of these 2 nodes (unless it is the median that gets
          moved up to the parent).  Finds Newitem, the median item that is
          to be moved up to the parent node.
  Return: NewItem        The item to be moved up into the parent node.
          NewRight       The pseudopointer to the child to the right of
                         NewItem (i.e. a pointer to the new RightNode).
*/
void BTTableClass::Split(const ItemType & CurrentItem, long CurrentRight,
   long CurrentRoot, int Location, ItemType & NewItem, long & NewRight)
   {
   int j, Median;
   NodeType RightNode;

   #ifdef DEBUG
      cout << "S";
   #endif

   if (Location < MinKeys)
      Median = MinKeys;
   else
      Median = MinKeys + 1;

   DataFile.seekg(CurrentRoot * NodeSize, ios::beg);
   DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

   #ifdef DEBUG
      cout << "R";
   #endif

   for (j = Median; j < MaxKeys; j++)
      {  // move half of the items to the RightNode
      RightNode.Key[j - Median] = CurrentNode.Key[j];
      RightNode.Branch[j - Median + 1] = CurrentNode.Branch[j + 1];
      }

   RightNode.Count = MaxKeys - Median;
   CurrentNode.Count = Median;   // is then incremented by AddItem

   // put CurrentItem in place
   if (Location < MinKeys)
      AddItem(CurrentItem, CurrentRight, CurrentNode, Location + 1);
   else
      AddItem(CurrentItem, CurrentRight, RightNode,
         Location - Median + 1);

   NewItem = CurrentNode.Key[CurrentNode.Count - 1];
   RightNode.Branch[0] = CurrentNode.Branch[CurrentNode.Count];
   CurrentNode.Count--;
   
   DataFile.seekp(CurrentRoot * NodeSize, ios::beg);
   DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);

   #ifdef DEBUG
      cout << "W";
   #endif

   NumNodes++;
   
   RightNode.Id = NumNodes;
   cout<<"\nNUM NODES = "<<NumNodes<<endl;
   NewRight = NumNodes;
   DataFile.seekp(NewRight * NodeSize, ios::beg);
   DataFile.write(reinterpret_cast <char *> (&RightNode), NodeSize);

   #ifdef DEBUG
      cout << "W";
   #endif
   }


/* Given:  The implicit BTTableClass object as well as:
           CurrentItem   The item to be inserted into the B-tree table.
           CurrentRoot   Pseudopointer to root of current subtree.
   Task:   To find where to put CurrentItem in a node of the subtree with
           the given root.  CurrentItem is ordinarily inserted, though
           a duplicate item is refused.  It is also possible that
           CurrentItem might be the item moved up to be inserted into
           the parent node if a split is done.
   Return: MoveUp        True if NewItem (and associated NewRight pointer)
                         must be placed in the parent node due to
                         splitting, false otherwise.
           NewItem       Item to be placed into parent node if a split was
                         done.
           NewRight      Pseudopointer to child to the right of NewItem.
*/
void BTTableClass::PushDown(ItemType & CurrentItem, long CurrentRoot,
   bool & MoveUp, ItemType & NewItem, long & NewRight)
   {
   int Location;
   ItemType mt ;
   #ifdef DEBUG
      cout << "P";
   #endif

   if (CurrentRoot == NilPtr)   // stopping case
      {   // cannot insert into empty tree
      MoveUp = true;
      NewItem = CurrentItem;
      NewRight = NilPtr;
      }
   else   // recursive case
      {
      DataFile.seekg(CurrentRoot * NodeSize, ios::beg);
      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "R";
      #endif

      if (SearchNode(CurrentItem.KeyField, Location,mt))////////////////////////////if (search node ){vector++}
       {
       cout<<"done";
       cout<<CurrentNode.Key[Location].ver;
   //    CurrentItem.ins[1]=atoi(CurrentItem.ver);
  /*       for (int i=0; i<5; i++)
             if ( CurrentNode.Key[Location].ins[i]==-1 && CurrentNode.Key[Location].OP=='I')
                {
                  CurrentNode.Key[Location].ins[i]=atoi(CurrentItem.ver);
                  break;                                       
                }
             else if ( CurrentNode.Key[Location].ins[i]==-1 && CurrentNode.Key[Location].OP=='D')
                  {
                  CurrentNode.Key[Location].del[i]=atoi(CurrentItem.ver);
                  break;                                       
                  }*/
                  
                  if (CurrentItem.OP=='I')
                     {
                        for (int i=0; i<5; i++) 
                            if ( CurrentNode.Key[Location].ins[i]==-1)
                               {
                                CurrentNode.Key[Location].ins[i]=atoi(CurrentItem.ver);
                                break;                                       
                                }               
                     }
                     else if(CurrentItem.OP=='D')
                     {
                          for (int i=0; i<5; i++) 
                            if ( CurrentNode.Key[Location].del[i]==-1)
                               {
                                CurrentNode.Key[Location].del[i]=atoi(CurrentItem.ver);
                                break;                                       
                                }    
                     }
    //   CurrentNode.Key[Location]=CurrentItem;
       DataFile.seekp(CurrentNode.Id* NodeSize, ios::beg);
       DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
    
       }//end if
     
     else{ 
           CurrentItem.ins[0]=-1;
           CurrentItem.ins[1]=-1;
           CurrentItem.ins[2]=-1;
           CurrentItem.ins[3]=-1;
           CurrentItem.ins[4]=-1;
           
           CurrentItem.del[0]=-1;
           CurrentItem.del[1]=-1;
           CurrentItem.del[2]=-1;
           CurrentItem.del[3]=-1;
           CurrentItem.del[4]=-1;
           
           if(CurrentItem.OP=='I')
           CurrentItem.ins[0]=atoi(CurrentItem.ver);
           else   CurrentItem.del[0]=atoi(CurrentItem.ver);
      
         PushDown(CurrentItem, CurrentNode.Branch[Location + 1], MoveUp,
         NewItem, NewRight);
         }
      
      if (MoveUp)
         {
         DataFile.seekg(CurrentRoot * NodeSize, ios::beg);
         DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

         #ifdef DEBUG
            cout << "R";
         #endif

         if (CurrentNode.Count < MaxKeys)
            {
            MoveUp = false;
            AddItem(NewItem, NewRight, CurrentNode, Location + 1);
            DataFile.seekp(CurrentRoot * NodeSize, ios::beg);
            DataFile.write(reinterpret_cast <char *> (&CurrentNode),
               NodeSize);

            #ifdef DEBUG
               cout << "W";
            #endif
            }
         else
            {
            MoveUp = true;
            Split(NewItem, NewRight, CurrentRoot, Location,
               NewItem, NewRight);
            }
         }
      }
   }


/* Given:   The implicit BTTableClass object as well as:
            Item with key = SearchKey to be deleted from the table.
   Task:    To delete Item with key = SearchKey from the table.
   Return:  In the function name, returns true to indicate success.
            (The implicit object is modified, of course.)
*/
bool BTTableClass::Delete( KeyFieldType SearchKey)
   {
   long CurrentRoot;
   long father;
   long sibling_pos;
   NodeType Sibling;
   int Location;
   bool Found;
   ItemType it;
   Found = false;
   CurrentRoot = Root;
   ItemType blanck;
   while ((CurrentRoot != NilPtr) && (! Found))
      {
      DataFile.seekg(CurrentRoot * NodeSize, ios::beg);
      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "R";
      #endif

      if (SearchNode(SearchKey, Location,it))
         {
         /* Here goes the code of delete*/
         Found = true;
         NumItems--;        
         
         int c = CurrentNode.Count-1;
         if (CurrentNode.Branch[0]==-1 && c>=MinKeys) 
         {
         /*Case 1 CurrentNode is Leaf Node*/
         for (int i = Location;i<CurrentNode.Count-1;i++)    CurrentNode.Key[i] = CurrentNode.Key[i+1];
         
         
         CurrentNode.Count --;
         
         DataFile.seekp(CurrentRoot * NodeSize, ios::beg);
         DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
         
         }
         else if (CurrentNode.Branch[0]==-1)
         {
            NodeType Father_Node;
            NodeType Right_Node;
            NodeType Left_Node;
            int loc;
            
            DataFile.seekg(father * NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&Father_Node), NodeSize);  
            
            for (int i = 0; i<MaxKeysPlusOne; i++) 
                {
                if (Father_Node.Branch[i] == CurrentNode.Id) loc = i;
                }
                
            
            NodeType RightSibling;
            NodeType LeftSibling;
            
            DataFile.seekg( Father_Node.Branch[loc+1]* NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&RightSibling), NodeSize);
            
            DataFile.seekg( Father_Node.Branch[loc-1]* NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&LeftSibling), NodeSize);
            
            //if for loading key from siblings
            if (Father_Node.Branch[loc+1]!=-1 && RightSibling.Count>MinKeys)
            {   
            //deleting from left subtree has right sibling  
            fstream Flll;
                 Flll.open("prim.dat", ios::in | ios::out|ios::binary);
                 if (Flll.fail())
                 Error("File cannot be opened");                            
            
            sibling_pos = Father_Node.Branch[loc+1];
            Flll.seekg( sibling_pos* NodeSize, ios::beg);
            Flll.read(reinterpret_cast <char *> (&Sibling), NodeSize);
            
            
            CurrentNode.Count++;
            CurrentNode.Key[CurrentNode.Count-1] = Father_Node.Key[loc];
            Father_Node.Key[loc] = Sibling.Key[0];
            for (int i =0 ;i<Sibling.Count-1;i++) Sibling.Key[i] = Sibling.Key[i+1];
            Sibling.Count--;
            
            for (int i = Location;i<CurrentNode.Count-1;i++)    CurrentNode.Key[i] = CurrentNode.Key[i+1];
                    CurrentNode.Count--;
            
            Flll.seekp(CurrentNode.Id * NodeSize, ios::beg);
         Flll.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
            
            Flll.seekp(father * NodeSize, ios::beg);
            Flll.write(reinterpret_cast <char *> (&Father_Node), NodeSize);
         
         Flll.seekp(Sibling.Id * NodeSize, ios::beg);
         Flll.write(reinterpret_cast <char *> (&Sibling), NodeSize);
            }
            else if (Father_Node.Branch[loc-1]!=-1 && LeftSibling.Count>MinKeys)
            {
                
            sibling_pos = Father_Node.Branch[loc-1];
            DataFile.seekg( sibling_pos* NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&Sibling), NodeSize);
            
            for (int i =1 ;i<CurrentNode.Count-1;i++) CurrentNode.Key[i] = CurrentNode.Key[i+1];
  
            CurrentNode.Key[0] = Father_Node.Key[loc-1];
            
           
            Father_Node.Key[loc-1] = Sibling.Key[Sibling.Count-1];
           // for (int i =1 ;CurrentNode.Count-1;i++) CurrentNode.Key[i] = Sibling.Key[i+1];
          
            Sibling.Count--;
            
            DataFile.seekp(CurrentNode.Id * NodeSize, ios::beg);
         DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
            
            DataFile.seekp(father * NodeSize, ios::beg);
            DataFile.write(reinterpret_cast <char *> (&Father_Node), NodeSize);
         
         DataFile.seekp(Sibling.Id * NodeSize, ios::beg);
         DataFile.write(reinterpret_cast <char *> (&Sibling), NodeSize);
            }
            else {
                 //non of siblings has >MinKeys values
                 fstream Fl;
                 Fl.open("prim.dat", ios::in | ios::out|ios::binary);
      if (Fl.fail())
         Error("File cannot be opened"); 
         
                 if (Father_Node.Branch[loc+1]!=-1)
                 {
                    //merging with right subtree  
                    cout<<"merging with right subtree";                              
            sibling_pos = Father_Node.Branch[loc+1];
            
            Fl.seekg( sibling_pos* NodeSize, ios::beg);
            Fl.read(reinterpret_cast <char *> (&Sibling), NodeSize);
            
                    
                    int x = Father_Node.Count;
                    
                  CurrentNode.Count++;
                 int   y = CurrentNode.Count-1;
                    CurrentNode.Key[y] = Father_Node.Key[loc];                          
                   
                  for (int i = 1;i<Sibling.Count;i++)
                    { 
                        CurrentNode.Count++;
                        CurrentNode.Key[CurrentNode.Count-1] = Sibling.Key[i-1];
                        
                        //Sibling.Count--;
                    }
                    CurrentNode.Count++;
                    y = CurrentNode.Count-1;
                    CurrentNode.Key[y] = Sibling.Key[Sibling.Count-1];
                   
                    
                    
                    
                    for (int i = loc;i<Father_Node.Count-1;i++) Father_Node.Key[i] =  Father_Node.Key[i+1];
                    
                    
                    for (int i = loc+1;i<Father_Node.Count;i++)Father_Node.Branch[i] = Father_Node.Branch[i+1];
                    Father_Node.Count --;
                    
                    Sibling.Count = 0;
                    
                    for (int i = Location;i<CurrentNode.Count-1;i++)    CurrentNode.Key[i] = CurrentNode.Key[i+1];
                    CurrentNode.Count--;
                    
         
   
                    if (Father_Node.Count == 0) 
                    {
                                          NodeType bla;
                                           BTTableClass::Root = 1;
                                         
                                        
                                          
                                          Fl.seekp(1 * NodeSize, ios::beg);
                                          Fl.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);                         
                                         
                    }
                    else  
                    {
                          
                    Fl.seekp(father * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&Father_Node), NodeSize);
                    
                    Fl.seekp(CurrentNode.Id * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
                    
                    Fl.seekp(sibling_pos * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&Sibling), NodeSize);
                    
                    }
                    
                    
                    
                 
                 }
                 
                 
                 else if (Father_Node.Branch[loc-1]!=-1)
                 {
                      
                   cout<<"Delete from right Sub Tree"<<endl;                               
            sibling_pos = Father_Node.Branch[loc-1];
            
            Fl.seekg( sibling_pos* NodeSize, ios::beg);
            Fl.read(reinterpret_cast <char *> (&Sibling), NodeSize);
               
            
            for (int i = Location;i<CurrentNode.Count-1;i++)    CurrentNode.Key[i] = CurrentNode.Key[i+1];
            CurrentNode.Count --;
            
            Sibling.Count++;
            Sibling.Key[Sibling.Count-1] = Father_Node.Key[loc-1];
            
            for (int i =0;i<CurrentNode.Count;i++)
            {
             Sibling.Count++;
             Sibling.Key[Sibling.Count-1] = CurrentNode.Key[i];
             
            }
       
            CurrentNode.Branch[loc] = -1;
   
            for (int i = loc-1;i<Father_Node.Count-1;i++) Father_Node.Key[i] =  Father_Node.Key[i+1];
                    
                    
            for (int i = loc-1;i<Father_Node.Count;i++)Father_Node.Branch[i] = Father_Node.Branch[i+1];
                    Father_Node.Count --;
                    
                    CurrentNode.Count = 0;
            
            
                    if (Father_Node.Count == 0) 
                    {
                                          NodeType bla;
                                           BTTableClass::Root = 1;
                                          
                                        
                                          
                                          Fl.seekp(3 * NodeSize, ios::beg);
                                          Fl.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
                                          
                                          Fl.seekp(father * NodeSize, ios::beg);
                                          Fl.write(reinterpret_cast <char *> (&bla), NodeSize);
                    
                                          Fl.seekp(sibling_pos * NodeSize, ios::beg);
                                          Fl.write(reinterpret_cast <char *> (&bla), NodeSize);
                                          
                                          Fl.seekp(3 * NodeSize, ios::beg);
                                          Fl.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
                    }
                    else  
                    {
                    Fl.seekp(father * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&Father_Node), NodeSize);
                    
                    Fl.seekp(CurrentNode.Id * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);
                    
                    Fl.seekp(sibling_pos * NodeSize, ios::beg);
                    Fl.write(reinterpret_cast <char *> (&Sibling), NodeSize);
                    
                    }



                 }//end else if
                 
                 }
          //end if from siblings
            
            
            
            
         }//end else if leaf 
         else
         {
		 cout<<"Deleting Key from internal Node"<<endl;
		
            
            NodeType RightSibling;
            NodeType LeftSibling;
            
            DataFile.seekg( CurrentNode.Branch[Location]* NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&LeftSibling), NodeSize);
            
            DataFile.seekg( CurrentNode.Branch[Location+1]* NodeSize, ios::beg);
            DataFile.read(reinterpret_cast <char *> (&RightSibling), NodeSize);
		    
		  if(LeftSibling.Count>MinKeys)
            {
                 cout<<"Taking Value from Left Node"<<endl;
                 CurrentNode.Key[Location] = LeftSibling.Key[LeftSibling.Count-1];
                 LeftSibling.Count--;
                 
                 DataFile.seekp(CurrentNode.Id * NodeSize, ios::beg);
                 DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);     
             
                 DataFile.seekp(LeftSibling.Id * NodeSize, ios::beg);
                 DataFile.write(reinterpret_cast <char *> (&LeftSibling), NodeSize); 
            }
		   else if (RightSibling.Count>MinKeys)
		    {
           cout<<"Taking Value from Right Node"<<endl;
             CurrentNode.Key[Location] = RightSibling.Key[0];
             for (int i = 0;i<RightSibling.Count-1;i++) RightSibling.Key[i] =  RightSibling.Key[i+1];
             RightSibling.Count--;   
             
             DataFile.seekp(CurrentNode.Id * NodeSize, ios::beg);
             DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);     
             
             DataFile.seekp(RightSibling.Id * NodeSize, ios::beg);
             DataFile.write(reinterpret_cast <char *> (&RightSibling), NodeSize);                     
            }
            else 
            {
                 cout<<"Merging siblings they both have MinKeys"<<endl;
                 cout<<"Right Sibling:"<<RightSibling.Id<<",Left S:"<<LeftSibling.Id<<endl;      
                 
                 for (int i = 0;i<RightSibling.Count;i++)
                 {
                 LeftSibling.Count++;
                 LeftSibling.Key[LeftSibling.Count-1] = RightSibling.Key[i];
                 }
                 
                 for (int i = Location; i<CurrentNode.Count-1;i++)
                 {
                     CurrentNode.Key[i] = CurrentNode.Key[i+1];
                 }
                 
                 for (int i = Location; i<CurrentNode.Count;i++)
                 {
                     CurrentNode.Branch[i] = CurrentNode.Branch[i+1]; 
                 }
                 
                 CurrentNode.Branch[Location] = LeftSibling.Id;
                 CurrentNode.Count--;
                 RightSibling.Count = 0;
                 
                 DataFile.seekp(CurrentNode.Id * NodeSize, ios::beg);
                 DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);     
             
                 DataFile.seekp(RightSibling.Id * NodeSize, ios::beg);
                 DataFile.write(reinterpret_cast <char *> (&RightSibling), NodeSize); 
                 
                 DataFile.seekp(LeftSibling.Id * NodeSize, ios::beg);
                 DataFile.write(reinterpret_cast <char *> (&LeftSibling), NodeSize);
            }
            
		    
		 }//end else
		 
		 
         }//end if Search Node
      
         
        
         
      else{
           father = CurrentRoot;
           CurrentRoot = CurrentNode.Branch[Location + 1];         
           }
      }

   return Found;
   }
   
   
bool BTTableClass::Insert( ItemType & Item)
   {
   bool MoveUp;
   long NewRight;
   ItemType NewItem;

   #ifdef DEBUG
      cout << "I";
   #endif
  // Item.ins[0]=atoi(Item.ver);
  // Item.ins[1]=atoi(Item.ver);
   PushDown(Item, Root, MoveUp, NewItem, NewRight);

   if (MoveUp)   // create a new root node
      {
      CurrentNode.Count = 1;
      CurrentNode.Key[0] = NewItem;
      CurrentNode.Branch[0] = Root;
      CurrentNode.Branch[1] = NewRight;
      NumNodes++;
      CurrentNode.Id = NumNodes;
    
      cout<<"\nNUM NODES = "<<NumNodes<<endl;
      Root = NumNodes;
      DataFile.seekp(NumNodes * NodeSize, ios::beg);
      DataFile.write(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "W";
      #endif
      }

   NumItems++;   // fixed 12/21/2001
   return true;   // no reason not to assume success
   }


/* Given:   The implicit BTTableClass object as well as:
            SearchKey   Key value to look for in the table.
   Task:    To look for SearchKey in the table.
   Return:  In the function name, true if SearchKey was found,
            false otherwise.
            Item        The item were SearchKey was found.
*/
bool BTTableClass::Retrieve(KeyFieldType SearchKey, ItemType & Item)
   {
                                
   long CurrentRoot;
   int Location;
   bool Found;
   ItemType it;
   Found = false;
   CurrentRoot = Root;

   while ((CurrentRoot != NilPtr) && (! Found))
      {
      DataFile.seekg(CurrentRoot * NodeSize, ios::beg);
      DataFile.read(reinterpret_cast <char *> (&CurrentNode), NodeSize);

      #ifdef DEBUG
         cout << "R";
      #endif

      if (SearchNode(SearchKey, Location,it))
         {
         Found = true;
         cout<<"\nLOCATION = "<<Location<<endl;
         Item = CurrentNode.Key[Location];
         
         
         }
      
        
         
      else
         CurrentRoot = CurrentNode.Branch[Location + 1];
      }

   return Found;
   }
#endif
