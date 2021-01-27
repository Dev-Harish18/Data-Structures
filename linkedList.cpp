#include<iostream>
using namespace std;

class Node{
    public:
        int data;
        Node *next;
};

class LinkedList{
    private:
        Node *first;
        void createFirstNode(int data);
        int deleteFirstNode();
    public:
        LinkedList(){
            first=NULL;
        }
        LinkedList(int a[],int size);
        void display();
        Node* getFirst();
        void setFirst(Node*);
        void insertFirst(int data);
        void insertLast(int data);
        void insertNodeAt(int index,int data);
        int deleteFirst();
        int deleteLast();
        int deleteNodeAt(int index);
        int search(int key);
        int count();
        int getMid();
        int loopLength();
        Node* reverse(Node *p);
        bool isPalindrome();      
};

//Private Member Functions
void LinkedList::createFirstNode(int data){
    first=new Node;
    first->data=data;
    first->next=NULL;
}
int LinkedList::deleteFirstNode(){
        Node *del=first;
        int deletedValue=del->data;
        delete del;
        first=NULL;
        return deletedValue;
}
//Member Functions definition


LinkedList::LinkedList(int arr[],int size){
    Node *temp,*spl;
    first=new Node;
    first->data=arr[0];
    temp=first;
    for(int i=1;i<size;i++){
        temp->next=new Node;
        temp=temp->next;
        temp->data=arr[i];
    }
    temp->next=NULL;
}

Node* LinkedList::getFirst(){
    return first;
}
void LinkedList::setFirst(Node *temp){
    first=temp;
}
void LinkedList::display(){
    Node *temp=first;
    if(first==NULL){
        throw "List is empty";
    }
    while(temp){
        cout<<temp->data<<" ";
        temp=temp->next;       
    }
    cout<<endl;
}

void LinkedList::insertFirst(int data){
    if(first==NULL){
        createFirstNode(data);
    }else{
        Node *temp=new Node;
        temp->data=data;
        temp->next=first;
        first=temp;
    }
}

void LinkedList::insertLast(int data){
    if(first==NULL){
        createFirstNode(data);
    }else{
        Node *temp;
        temp=first;
        while(temp->next)
            temp=temp->next;
        temp->next=new Node;
        temp=temp->next;
        temp->data=data;
        temp->next=NULL;
    }
}

void LinkedList::insertNodeAt(int index,int data){
    Node *temp=first;
    int size=count();

    if(index<0 && index>=size){
        throw "Index is invalid\n";            
    }
    if(index==0){
        insertFirst(data);
        return;
    }        
    for(int i=0;i<index-1;i++)
        temp=temp->next;
    Node *newNode=new Node;
    newNode->data=data;
    newNode->next=temp->next;
    temp->next=newNode;
}

int LinkedList::deleteFirst(){
    if(first==NULL)
        throw "Delete Operation can't be done in empty list\n";   
    if(first->next==NULL)
      return  deleteFirstNode();   
    Node *del=first;
    int deletedValue=del->data;
    first=del->next;
    delete del;
    return deletedValue; 
}

int LinkedList::deleteLast(){
    if(first==NULL)
        throw "Deletion operation can't be done in empty list";
    if(first->next==NULL)
        return deleteFirstNode();
    Node *temp=first,*del;
    int deletedValue;
    while(temp->next->next)
        temp=temp->next;
    del=temp->next;
    deletedValue=del->data;
    temp->next=NULL;
    delete del;
    return deletedValue;
}

int LinkedList::deleteNodeAt(int index){
    Node *temp=first;
    int size=count();

    if(index<0 && index>=size)
        throw "Index is invalid\n";
    
    if(index==0)
        return deleteFirst();
    
    for(int i=0;i<index-1;i++)
        temp=temp->next;
    Node *del=temp->next;
    temp->next=del->next;
    int deletedValue=del->data;
    delete del;
    return deletedValue;
}

int LinkedList::count(){
    Node *temp=first;
    int count=0;

    while(temp){
        temp=temp->next;
        count++;
    } 
    return count;
}

int LinkedList::search(int key){
    Node *temp=first;
    int pos=0;
    while(temp && temp->data!=key){
        temp=temp->next;
        pos++;
    }
        
    if(temp)
        return pos;
    else
        return -1;
}

int LinkedList::getMid(){
    Node *fast,*slow;
    fast=slow=first;
    while(fast->next){
        slow=slow->next;
        fast=fast->next->next?fast->next->next:fast->next;
    }
    return slow->data;
}

int LinkedList::loopLength(){
    Node *slow,*fast,*temp;
    int count=0;
    slow=fast=first;
    do{
        if(first->next){
            slow=slow->next;
            fast=fast->next->next?fast->next->next:fast->next;
        }
    }while(fast!=slow && fast->next);
    if(fast->next==NULL){
        return -1;
    }
    temp=slow;
    do{
        temp=temp->next;
        count++;
    }while(temp!=slow);
    return count;
}

Node* LinkedList::reverse(Node *temp){
    Node *p=temp,*q=NULL,*r=NULL;
    while(p){
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    temp=q;
    return temp;
}

bool LinkedList::isPalindrome(){
    Node *slow=first;
    Node *fast=first;
    Node *second;
    
    while(true){
        fast=fast->next->next;
        //Even
        if(fast==NULL){
            second=slow->next;
            slow->next=NULL;
            break;
        }
        //Odd
        if(fast->next==NULL){
            second=slow->next->next;
            slow->next=NULL;
            break;
        }
        slow=slow->next;
    }
    second=reverse(second);

    Node *i=first,*j=second;

    while( i && j && i->data == j->data ){
        i=i->next;
        j=j->next;
    }
    if(i||j)
        return false;
    return true;
}

int main(){
    int arr[]={1,2,1,2,1};
    LinkedList list(arr,5);
    try{
       list.display();
       list.setFirst(list.reverse(list.getFirst()));
       list.display();
       cout<<boolalpha<<list.isPalindrome();
    }catch(const char *err){
        cout<<err;
    }
}