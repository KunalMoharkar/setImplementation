#include <iostream>
#include <string>
#define MAX_SET_CAPACITY 101

using namespace std;

//chain of hashtable for collisions
struct list{

    string data;
    list *next;
};

//hashtable structure
struct hashtable{

    list* arr[MAX_SET_CAPACITY];
};

//set structure
struct set{

    hashtable values;
    int size;
};


void initialize_hash(hashtable* h);
int hash_val(string str);
void insert_hash(hashtable* h, string str) ;
list* makenode(string str);
void show_hash(hashtable *h);
int find_hash(hashtable* h,string str);
int delete_hash(hashtable* h,string str);
void initialize_set(set* s);
void insert_set(set* s,string str);
void show_set(set* s);//enumerate
int delete_set(set* s,string str);
bool isElementOf(set *s,string str);
int isEmpty(set *s);
int cardinality(set *s);
set* build(string arr[],int size);
set* create();
set* union_set(set* s1, set* s2);
set* intersection_set(set* s1,set* s2);
set* difference_set(set* s1,set* s2);
int subset(set* s1,set* s2);

int main()
{   
    int num,i;
    string arr[100];
    string val="";
    set *s1,*s2,*s;

    cout<<"\nSTATIC SET OPERATIONS:\n";
    cout<<"Enter the no. of Elements of set\n";
    cin>>num;

    for(i=0;i<num;i++)
    {
        cin>>arr[i];
    }
    cout<<"\nBuilding the set.....\n";
    s = build(arr,num);

    num = 0 ;
    while(num!=-1)
    {
        cout<<"\npress: 1.is_empty 2.size 3.enumerate 4.is_element -1 to quit\n";
        cin>>num;

        switch (num)
        {
            case 1:

                if(isEmpty(s))
                {
                    cout<<"set is empty\n";
                }
                else
                {
                    cout<<"Not Empty\n";
                }
                break;

            case 2:
        
                cout<<"Size of set is\n";
                cout<<cardinality(s);
                break;

            case 3:
                cout<<"The set is\n";
                show_set(s);
                break;
            case 4:
                cout<<"Enter the element \n";
                cin>>val;
                
                if(isElementOf(s,val))
                {
                    cout<<"it is the element of set\n";
                }
                else
                {
                     cout<<"not a element of set\n";
                }
            
                break;   
            
            default:
                break;
        }


    }

    cout<<"\n DYNAMIC OPERATIONS ON A SET\n";

    cout<<"creating set....";

    s = create();
    
     num = 0 ;
    while(num!=-1)
    {
        cout<<"\npress: 1.add element 2.delete element -1 to quit\n";
        cin>>num;

        switch (num)
        {
            case 1:
                cout<<"Enter the element to add \n";
                cin>>val;

                insert_set(s,val);
                show_set(s);
                break;

            case 2:

                cout<<"Enter the element to be deleted \n";
                cin>>val;
                
                if(delete_set(s,val))
                {
                    show_set(s);
                }
                else
                {
                     cout<<"element does not exist in the set";
                     show_set(s);
                }
            
                break;   
            
            default:
                break;
        }


    }



    


















    cout<<"\n Operations of a set:\n";


    s1 = create();
    
    val="";

    while(val.compare("quit"))
    {   
        cout<<"Enter Element of set 1----enter quit when done\n";

        cin>>val;
        if(val.compare("quit"))
        {
            insert_set(s1,val);
        }
    }

   
    s2 = create();
    val = "";

    while(val.compare("quit"))
    {   
        cout<<"Enter Element of set 2----enter quit when done\n";

        cin>>val;
        if(val.compare("quit"))
        {
            insert_set(s2,val);
        }
    }

    cout<<"SET 1:";
    show_set(s1);
    cout<<"SET 2:";
    show_set(s2);

    s = union_set(s1,s2);
    cout<<"\nUNION OF SETS IS:\n";
    show_set(s);

    s = intersection_set(s1,s2);
    cout<<"\nINTERSECTION OF SETS IS:\n";
    show_set(s);
    
    s = difference_set(s1,s2);
    cout<<"\nDIFFERENCE OF SETS IS:\n";
    show_set(s);
    
    cout<<"\nIS SUBSET:\n";
    if(subset(s1,s2))
    {
        cout<<"set 1 is a subset of set 2\n";
    }
    else
    {
        cout<<"not a subset\n";
    }
    
    
    
}
//allocate memory for node and set data
list* makenode(string str)
{   
    list *nptr;
    nptr = new list;
    nptr->next = NULL;
    nptr->data =  str;

    return nptr;
}
//initialize the hashtable
void initialize_hash(hashtable* h)
{
    int i;

    for(i=0;i<MAX_SET_CAPACITY;i++)
    {
        h->arr[i] = NULL;
    }

}
//insertion in hash table
void insert_hash(hashtable* h, string str) 
{
    list *nptr,*ptr;
    int index;
    nptr = makenode(str);
    index = hash_val(str);

    ptr = h->arr[index];//head pointer

    if(ptr!=NULL)//normal LL insertion
    {

        while(ptr->next!=NULL)
        {
            ptr = ptr->next;
        }

        ptr->next = nptr;

    }
    else
    {
        h->arr[index]= nptr;//make new node as head
    }
    

}
//hashing the string
int hash_val(string str)
{
    int sum,i;
    sum = 0;
    
    for(i=0;i<str.length();i++)//hashfunction sum of asscii values
    {
        sum+=i*(int)str[i];
    }

    return (sum%MAX_SET_CAPACITY);

}
//printout the hash structure 
void show_hash(hashtable* h)
{
    int i;
    list *ptr;

    cout<<"\n{";

    for(i=0;i<MAX_SET_CAPACITY;i++)
    {
        ptr = h->arr[i];

        while(ptr!=NULL)
        {
            cout<<ptr->data<<",";
            ptr= ptr->next;
        }

    }
    cout<<"}\n";


}
//search for a value in hash table
int find_hash(hashtable* h,string str)
{
    int index,found=0;
    list *ptr;
    index = hash_val(str);

    ptr = h->arr[index];

    if(ptr!=NULL)
    {
        while(ptr!=NULL&&found==0)
        {   
            if(ptr->data.compare(str)==0)
            {
                found = 1;
            }

            ptr = ptr->next;
        }
    }

    return found;
    
}
//deletion from hash table
int delete_hash(hashtable* h,string str)
{   
    int index,retval=0;
    list *ptr,*prev,*current;
    index = hash_val(str);

    if(find_hash(h,str))//proceed only when element is present
    {   
        retval =1;
        ptr = h->arr[index];
        int found = 0;
        prev = NULL;
        current = NULL;

        while(ptr!=NULL&&found==0)
        {   
            prev = current;
            current = ptr;
            
            if(ptr->data.compare(str)==0)
            {
                found = 1;
            }
            
            ptr = ptr->next;
        }

        if(prev==NULL && current == h->arr[index])//head node to be deleted
        {
            h->arr[index] = ptr;
        }
        else
        {
            prev->next = ptr;
        }
        

    }


    return retval;

}
//initializing the set
void initialize_set(set* s)
{
    s->size = 0;
    initialize_hash(&s->values);
}
//add an element into the set
void insert_set(set* s,string str)
{   

    if(!find_hash(&s->values,str))//No duplicates allowed
    {
        insert_hash(&s->values,str);
        s->size++;//increase the size by 1
        
    }


}
//delete from set
int delete_set(set* s,string str)
{
    int retval = 0;

    if(delete_hash(&s->values,str))//Delete only when element present
    {
        retval = 1;
        s->size--;//decreade the size by 1
    }

    return retval;
}
//display the set
void show_set(set* s)
{
    show_hash(&s->values);
}
//check whether a element is present in set
bool isElementOf(set* s,string str)
{
    int retval = false;
    if(find_hash(&s->values,str))
    {
        retval = true;
    }
    return retval;
}
//check if set is empty
int isEmpty(set *s)
{
    int retval = 0;
    if(s->size == 0)
    {
        retval = 1;
    }
    return retval;
}
//get the no of elements in the set
int cardinality(set *s)
{
    return s->size;
}
//builds a set with a given list of items 
set* build(string arr[],int size)
{   
    set *s;
    int i;
    s = new set;
    initialize_set(s);
    
    for(i=0;i<size;i++)
    {
        if(!find_hash(&s->values,arr[i]))
        {
            insert_hash(&s->values,arr[i]);
            s->size++;
        }
    }

    return s;
}
//creates a empty set
set* create()
{
    set *s;
    s = new set;
    initialize_set(s);

    return s;
}

set* union_set(set* s1,set*s2)
{
    int i;
    list *ptr;
    set *s = create();

    //traverse both sets

    for(i=0;i<MAX_SET_CAPACITY;i++)
    {
        ptr = s1->values.arr[i];

        while(ptr!=NULL)
        {
            insert_set(s,ptr->data);
            ptr = ptr->next;
        }

    }

     for(i=0;i<MAX_SET_CAPACITY;i++)
    {
        ptr = s2->values.arr[i];

        while(ptr!=NULL)
        {   
            if(!isElementOf(s,ptr->data))//insert only when not currently inserted
            {
                insert_set(s,ptr->data);
            }    
            ptr = ptr->next;
        }

    }

    return s;

}
//intersection of set
set *intersection_set(set* s1,set* s2)
{
    int i;
    list *ptr;
    set *s = create();

    for(i=0;i<MAX_SET_CAPACITY;i++)//traverse set 1
    {
        ptr = s1->values.arr[i];

        while(ptr!=NULL)
        {
            if(isElementOf(s2,ptr->data))//insert those elements which are in set 2
            {
                insert_set(s,ptr->data);
            }    
            ptr = ptr->next;
        }

    }   

    return s;

}
//difference in sets set1-set2
set *difference_set(set* s1,set* s2)
{
     int i;
    list *ptr;
    set *s = create();

    for(i=0;i<MAX_SET_CAPACITY;i++)//travere set 1
    {
        ptr = s1->values.arr[i];

        while(ptr!=NULL)
        {
            if(!isElementOf(s2,ptr->data))//insert those elements which are not in set 2
            {
                insert_set(s,ptr->data);
            }    
            ptr = ptr->next;
        }

    }   

    return s;

}
//ckeack if set 1 is a subset of set 2
int subset(set* s1,set* s2)
{
    
    int i;
    list *ptr;

    for(i=0;i<MAX_SET_CAPACITY;i++)//traverse set 1
    {
        ptr = s1->values.arr[i];

        while(ptr!=NULL)
        {
            if(!isElementOf(s2,ptr->data))//return if not presemt in set 2
            {
                return 0;
            }    
            ptr = ptr->next;
        }

    }   

    return 1;

}
