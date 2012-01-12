/*
  Name: PROJECT 5: THE DOG SHOW
  Author: JULIO JOSE REYES III
  Date: 11/12/09 15:36
  Description: This program will simulate judging at a "Dog Conformation Championship" 
  for the "Best in Show", 
  an event in which the winners from the various breed categories compete to determine 
  which dog has qualities that most closely match the highest of all possible 
  standard categories for their particular breed. The user will play the role of the judge.
  The design of the program uses a circular doubly-linked list to simulate this experience.
  
  This program give the user these commands to use for the program:
       'C':  create a circular doubly-linked list of dogs according to
		        the order in which the judge initially positions them.

		'P':  "prints" (actually sends to the display and to the external text 
        file, "dogs.txt")  the line of dogs, according to their position,
		        giving the position, id number, name, and breed of the dog.

		'F':  "prints" (actually sends to the display and to the external text 
        file, "dogs.txt") the id number, name, and breed of the first dog
	        in the line.

		'L':  "prints" (actually sends to the display and to the external text 
        file, "dogs.txt") the id number, name, and breed of the last dog
		        in the line.

		'D':  allows the user (judge) to delete a dog from the line without
		replacing it with another dog.  The dog to be deleted is to be 
        identified by id number.  If the dog is in t he line, then your 
        program is to send a message to both the screen and to the 
        external text file that confirms that the dog (id number, name, 
        and breed) was removed. If the dog is not in the line, your 
        program is to send an appropriate message to the screen and 
        to the external text file.

        'DR': allows the user (judge) to delete a dog from the line and
        replace it with another dog who is currently in line.  Again, the 
        dog to be deleted is to be identified by id number, name and 
        breed both at the screen and in the external text file.  If a dog 
        is not in the line, then your program is to send an appropriate 
        message to the screen and to the external text file.

        'R':    allows the user (judge) to reposition a dog in the line.  
        
        'S':  show the position of a dog whom the user (judge) specifies by
               id number.  Your program is to announce the position of the
               dog along with the dog's id number, name and breed both at 
               the screen and in the external text file.  If the dog is not in the 
               line, your program is to provide an appropriate message at the 
               screen and the external text file.
        
        'Q': allow the user (judge) to announce the winner( the first place 
              dog) both at the screen and in the external text file,and to quit 
              the program .

*/

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<cctype>
#include<fstream>
using namespace std;

struct Nodetype;
typedef Nodetype* Nodeptr;

struct Nodetype //struct to hold information about each dog
{
  int id;
  char name[20];
  char breed[50];
  int position; //Keeps track of the position of the dog in the line
  Nodeptr Left, Right;
  int numnodes;  //Field is used only in the header node to keep track of # nodes

};

ofstream outs;

int main()
{
    // Open the external file 
    outs.open("Dogs.txt",ios::app);
        
      char ch1, ch2, choice[3];
        
      Nodeptr Head;
    
        
        // Function Prototypes
      void menu();
      void DescribeProgram();
      Nodeptr InitializeHeader();
      void Addnewnode(Nodeptr Head);
      void PrintList(Nodeptr Head);
      void PrintFirst(Nodeptr Head);
      void PrintLast(Nodeptr Head);
      void Deletenode(Nodeptr Head);
      void Printanode(Nodeptr Head);
      void Replacenode(Nodeptr Head);
      void Reposition(Nodeptr Head);
      void Announce_Winner(Nodeptr Head);
      Nodeptr Search(Nodeptr Head, int id);
   	  bool Empty(Nodeptr Head);
    
   	  Head = InitializeHeader();
    
    // Activate Menu
      DescribeProgram();
   	  menu();
   	  cout<<endl;
     
      strcpy(choice, "");
      cout<<"Enter your choice: ";
      cin.getline(choice,3);
      ch1 = choice[0];
      ch1 = toupper(ch1);
      ch2 = choice[1];
      ch2 = toupper(ch2);
      while (ch1 != 'Q')
      {
           switch(ch1)
           {
      	 case 'C':Addnewnode(Head);
      		  break;
      	 case 'P':PrintList(Head);
      		  break;
      	 case 'F': PrintFirst(Head);
      		  break;
      	 case 'L':PrintLast(Head);
      		  break;
      	 case 'D':switch(ch2)
      		  {
      		   case 'R':Replacenode(Head);
      		                 break;
      		   case '\0': Deletenode(Head);
      		                  break;
      		  }
      		   break;
      	 case 'R': Reposition(Head);
      		   break;
      	 case 'S': Printanode(Head);
      		   break;
           default : cout<<"Invalid choice. Try again!"<<endl;
        }
           cout<<endl;
           menu();
           strcpy(choice, "");
           cout<<"Please enter your choice."<<endl;
           cin.getline(choice,3);
      	   ch1 = choice[0];
      	   ch1 = toupper(ch1);
           ch2 = choice[1];
           ch2 = toupper(ch2);
      }
      
      Announce_Winner(Head);
      outs.close();	
      system("PAUSE");
      return 0;
}

void DescribeProgram()
{
  cout<<"Welcome to the Dog Conformation Championship!!!"<<endl;
  cout<<"This program will help you in your judgement in"<<endl;
  cout<<"in your selection on which dog will be the Best in Show"<<endl;
  cout<<"This program uses a circular doubly-linked list so the"<<endl;
  cout<<"Dog's information is properly stored. The list must be"<<endl;
  cout<<"created first, then it can be altered by using the following"<<endl;
  cout<<"commands below."<<endl;
  cout<<""<<endl;
  cout<<endl;

}   

void menu()
{
  cout<<"C or c    <-1- Create a list of dogs."<<endl;
  cout<<"P or p    <-2- Print the list of dogs by position in list."<<endl;
  cout<<"F or f    <-3- Print id and breed of dog at head of list."<<endl;
  cout<<"L or l    <-4- Print id and breed of dog at end of list."<<endl;
  cout<<"D or d    <-5- Delete a dog, identified by id."<<endl;
  cout<<"S or s    <-6- Show the position of dogs in list."<<endl;
  cout<<"R or r    <-7- Reposition a dog in the list."<<endl;
  cout<<"DR or dr  <-8- Delete and Replace dog who is currently in list"<<endl;
  cout<<"Q or q    <-9- Quit the program." <<endl;
  cout<<endl;
}

Nodeptr InitializeHeader()
{
    Nodeptr q;
   	q = new Nodetype;
   	q->Right = q;
   	q->Left = q;
   	q->numnodes = 0;
   	q->position = 0;
   	return q;
}

void Addnewnode(Nodeptr Head)
{
  Nodeptr p,q;
  int idnum;
  int count;
  bool Empty(Nodeptr List);                        
  Nodeptr Search(Nodeptr List, int num);   
  cout<<"Enter id number of the dog(-1 to stop):";
  cin>>idnum;
  cin.ignore();
  count = 0;
  while(idnum != -1)
     {
	p = Search(Head, idnum);
	if (p != NULL)
	   cout<<"This dog is already in line!"<<endl;
	else
	   {
	     count++;
	     q = new Nodetype;
	     q->id = idnum;
	     cout<<"Enter the dog's name:";
	     cin.getline(q->name,20);
	     cout<<"Enter the dog's breed:";
	     cin.getline(q->breed,50);
	     q->position = count;
	     p = Head->Left;
	     q->Right = Head;
	     q->Left = p;
	     p->Right = q;
	     Head->Left = q;
	     Head->numnodes++;
	   }
	cout<<endl;
	cout<<"Enter id number of the dog(-1 to stop):";
	cin>>idnum;
	cin.ignore();
     }
  return;
}

Nodeptr Search(Nodeptr Head, int idnum)
{
  int found = 0;
  Nodeptr p;
  bool Empty(Nodeptr List);
  
  if (Empty(Head))
     return NULL;
  else
  {
    p = Head->Right;
    do
	{
  	 if (idnum == p->id)
    	  found = 1;
  	 else
	      p = p->Right;
		
    }while (!found &&(p != Head));
    
    if (p != Head)
	  return p;
    else
	  return NULL;
   }
}

Nodeptr Search2(Nodeptr Head, int pos)
{
  int found = 0;
  Nodeptr p;
  bool Empty(Nodeptr List);
  
  if (Empty(Head))
     return NULL;
  else
     {
       p = Head->Right;
       do
	 {
	   if (pos == p->position)
	      found = 1;
	   else
	      p = p->Right;
		
	  }while (!found &&(p != Head));
       if (p != Head)
	  return p;
       else
	  return NULL;
     }
}

void PrintFirst(Nodeptr Head)
{
  bool Empty(Nodeptr List);

  if(Empty(Head))
     cout<<"Empty List!"<<endl;
  else
  {
   cout<<endl;
   cout<<"The dog at the head of the list is:\n";
   cout<<"# "<<Head->Right->id<<": "<<Head->Right->name<<Head->Right->breed<<endl;
   
   outs<<endl;
   outs<<"The dog at the head of the list is:\n";
   outs<<"# "<<Head->Right->id<<": "<<Head->Right->name<<Head->Right->breed<<endl;
  }
  cout<<endl;
  outs<<endl;

  return;
}

void PrintLast(Nodeptr Head)
{
  bool Empty(Nodeptr List);

  if(Empty(Head))
     cout<<"Empty List!"<<endl;
  else
  {
   cout<<endl;
   cout<<"The dog at the end of the list is:\n";
   cout<<"# "<<Head->Left->id<<": "<<Head->Left->name<<"  "<<Head->Left->breed<<endl;
   
   outs<<endl;
   outs<<"The dog at the end of the list is:\n";
   outs<<"# "<<Head->Left->id<<": "<<Head->Left->name<<"  "<<Head->Left->breed<<endl;
  }
  cout<<endl;

  return;
}
void PrintList(Nodeptr Head)
{
      Nodeptr p;
      bool Empty(Nodeptr List);

      p = Head;
      if (Empty(Head))
          cout<<"!This list is empty!"<<endl;
      else
      {
    	   cout<<"Here is your current list of dogs:" << endl << endl;
    	   cout<<"ID: "<<setw(15)<<"Name: "<<setw(17)<<"Breed: " << endl;
    	   
    	   outs<<"Here is your current list of dogs:" << endl << endl;
    	   outs<<"ID: "<<setw(15)<<"Name: "<<setw(17)<<"Breed: " << endl;
    	 
    	  do
    	  {
    	     p = p->Right;
    	     cout << right << setw(4) << p->id << setw(13) << p->name << setw(13)
                 <<"  "<< left << setw(13) << p->breed <<endl;
             outs << right << setw(4) << p->id << setw(13) << p->name << setw(13)
                 <<"  "<< left << setw(13) << p->breed <<endl;
    	  }while (p->Right !=Head);
      }
    	cout << right;

   return;
}

void Replacenode(Nodeptr Head)
{
      Nodeptr p,q;
   	  int idnum, count;
   	  bool Empty(Nodeptr List);
   	  //Searches a node based upon id number of dog provided
   	  Nodeptr Search(Nodeptr List, int num);
   	  if (Empty(Head))
         cout<<"Empty List!"<<endl;
      else
      {
          cout<<"Enter id number of the dog you wish to replace."<<endl;
          cin>>idnum;
  	      cin.ignore();
          p = Search(Head, idnum);
          if (p==NULL)
  	        cout<<"The dog is not in the line!"<<endl;
          else
          {
              cout<<"Enter id number of the replacement dog."<<endl;
              cin>>idnum;
  	          cin.ignore();
              q = Search(Head, idnum);
              if (q==NULL)
  	             cout<<"The dog is not in the line!"<<endl;
              else
              {
                   // Replace the dog by replacing node
                   p->id = q->id;
                   strcpy(p->name, q->name);
                   strcpy(p->breed, q->breed);
                   q->Left->Right = q->Right;
                   q->Right->Left = q->Left;
                   delete q;
              }// end if
          }// end if
          
          outs << "Dog has been replaced." << endl;
      }// end if
      
   return;
}

void Deletenode(Nodeptr Head)
{
   int idnum;
   int count;
   Nodeptr p;
   Nodeptr Search(Nodeptr List, int num);
   bool Empty(Nodeptr List);
  
   if (Empty(Head))
      cout<<"Empty List!"<<endl;
   else
   {
        cout<<"Enter id number of the dog you wish to delete."<<endl;
        cin>>idnum;
  	    cin.ignore();
        p = Search(Head, idnum);
    if (p==NULL)
  	 cout<<"The dog is not in the line!"<<endl;
    else
  	{
  	   p->Left->Right = p->Right;
  	   p->Right->Left = p->Left;
  	   delete p;
  	   Head->numnodes--;
  	   cout<<"Dog "<<idnum<<" removed from the line!"<<endl<<endl;
  	   outs<<"Dog "<<idnum<<" removed from the line!"<<endl<<endl;
  	   p = Head->Right;
  	   count = 0;
  	   
  	   while(p !=Head)
  	   {
  		   count++;
  		   p->position = count;
  		   p = p->Right;
  	   }
  	 }
   }
   return;
}

void Reposition(Nodeptr Head)
{
     Nodeptr p,q;
     int count, pos1, pos2;
	
	 bool Empty(Nodeptr List);
	
  		//This function searches for a dog based upon position in the line.
  		//It returns a pointer to the node (dog) if the position exists and
  		//NULL if it does not.  See below for the actual function.
  
	 Nodeptr Search2(Nodeptr List, int pos);
     if (Empty(Head))
      cout<<"Empty List!"<<endl;
     else
     {
        cout<<"Enter the position of the dog."<<endl;
        cin>>pos1;
  	    cin.ignore();
        p = Search2(Head, pos1);
        if (p == NULL)
         cout<<"The dog is not in the line!"<<endl;
        else
        {
            cout<<"Enter the position you wish to put the dog."<<endl;
            cin>>pos2;
  	        cin.ignore();
            q = Search2(Head, pos2);
            if (q == NULL)
               cout<<"The dog is not in the line!"<<endl;
            else
            {
                // Remove p a.k.a. the first position from the node
                p->Left->Right = p->Right;
                p->Right->Left = p->Left;
                if(pos1 < pos2)
                {      
                        p->Right = q->Right;
                        q->Right->Left = p;
                        p->Left = q;
                        q->Right = p;       
                }
                if(pos1 > pos2)
                {
                        p->Left = q->Left;
                        q->Left->Right = p;
                        q->Left = p;
                        p->Right = q;                                                    
                }//end if
            }//end if..else
            
            // Traverse the list
            p = Head->Right;
  	        count = 0;
  	   
  	        while(p !=Head)
  	        {
               count++;
  		       p->position = count;
  		       p = p->Right;
            }
            
            cout << "Dogs in "<<pos1<<" and "<<pos2<< " have been repositioned." << endl;
            outs << "Dogs in "<<pos1<<" and "<<pos2<< " have been repositioned." << endl;
            
        }//end if..else
     }//end if..else 
	return;	
}

void Printanode(Nodeptr Head)
{
  int idnum;
  Nodeptr p;
  int Empty(Nodeptr List);
  Nodeptr Search(Nodeptr List,int id);

  if (Empty(Head))
     cout<<"Empty List!"<<endl;
  else
     {
       cout<<"Enter id number of the client."<<endl;
       cin>>idnum;
	   cin.ignore();
       p = Search(Head,idnum);
       if (p == NULL)
	  cout<<"That dog is not in the list!"<<endl;
       else
	  {
	     
	     cout<<"---- SELECTED NODE ----" << endl;
		 cout<<"Position #"<< p->position << endl;
         cout<<"Name: " << p->name<<endl;
         cout<<"Breed: " << p->breed << endl << endl;
         
         // Send to the external file
         outs<<"---- SELECTED NODE ----" << endl;
		 outs<<"Position #"<< p->position << endl;
         outs<<"Name: " << p->name<<endl;
         outs<<"Breed: " << p->breed << endl << endl;
		
	  }
     }
  return;
}


bool Empty(Nodeptr Head)
{
   if ((Head->Right == Head) && (Head->Left == Head))
      return true;
   else
      return false;
}

void Announce_Winner(Nodeptr Head)
{
     cout<<"-----FINAL RESULT -----"<<endl;
     outs<<"-----FINAL RESULT -----"<<endl;
     
     cout<<"Throughout tough decision-making and proper judgement, our judges"<<endl;
     cout<<"have decided that the winner of this Dog Show is:...\n\n";
     
     outs<<"Throughout tough decision-making and proper judgement, our judges"<<endl;
     outs<<"have decided that the winner of this Dog Show is:...\n\n"; 
     
     cout<<"Dog# "<<Head->Right->id<<": "<<Head->Right->name<<" the "<<Head->Right->breed<<endl;
     outs<<"Dog# "<<Head->Right->id<<": "<<Head->Right->name<<" the "<<Head->Right->breed<<endl;
     cout<<endl;
     outs<<endl;
     
}
