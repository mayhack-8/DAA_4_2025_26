#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};
class Stack {
    public:
    Node* top;
    int c;
    Stack() {
        top = nullptr;
        c=0;
    }
    void push(int x){
        Node*temp=new Node(x);
        if(!top){
            top=temp;
            return;
        }
        temp->next=top;
        top=temp;
        c++;
    }
    void pop(){
       if(isEmpty()){
          return;
        } 
        Node* temp=top;
        top=top->next;
        delete temp;
        c--;
    }
    bool isEmpty(){
        if(top==nullptr){
            return true;
        }
        else{
            return false;
        }
        }
    
    void topvalue(){
        if (top==nullptr) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Top element is: " << top->data << endl;    
    }
    void size(){
        cout<<"size:"<<c<<endl;
    }
   
    void display(){
        if (top==nullptr){
            cout<<"stack is Empty"<<endl;
            return;
        }
        Node*temp=top;
        while(temp!=nullptr){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }
};
int main(){
    Stack s;
    s.push(1);
    s.push(2);
    s.display();
    s.pop();
    s.topvalue();
    s.push(3);
    s.size();
    s.pop();
    s.isEmpty();
}

