#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};
void insertAtHead(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head != nullptr) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
}
void insertAtEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}
void InsertAtPosition(Node*& head, int pos, int val) {
    if (pos == 0) {
        insertAtHead(head, val);
        return;
    }
    Node* newNode = new Node(val);
    Node* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        insertAtEnd(head, val);
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}
void deleteAtHead(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}
void deleteAtEnd(Node*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->prev->next = nullptr;
    delete temp;
} 
void deleteAtPosition(Node*& head, int pos) {
    if (head == nullptr) return;
    if (pos == 0) {
        deleteAtHead(head);
        return;
    }
    Node* temp = head;
    for (int i = 0; i < pos && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) return;
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    delete temp;
}  
void display(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtHead(head, 5);
    InsertAtPosition(head, 1, 15);
    display(head); 
    deleteAtPosition(head, 2);
    display(head); 
    deleteAtHead(head);
    display(head); 
    deleteAtEnd(head);
    display(head); 
    return 0;
}
