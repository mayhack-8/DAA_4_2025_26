#include<bits/stdc++.h>

using namespace std;

#define MAX 100
int heapSize=0;

int heap[MAX];
//insertion
void heapifyUp(int i) {

while(i>0 && heap[(i-1)/2]> heap[i]) {

swap(heap[i] , heap[(i-1)/2]);
i = (i-1)/2;
}
}

void insert(int val) {

if(heapSize==MAX) {
cout<<"heap full";
return;
}
heap[heapSize] = val;
heapSize++;
heapifyUp(heapSize-1);

}
//deletion (root index)
void heapifyDown(int i){
    int smallest=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<heapSize && heap[smallest]>heap[l])
    smallest=l;
    if (r<heapSize && heap[smallest]>heap[r])
    smallest=r;
    if (smallest!=i){
        swap(heap[smallest],heap[i]);
        heapifyDown(smallest);
    }

}
void deleteMin(){
    if (heapSize==0){
        cout<<"heap is empty";
        return;
    }
    heap[0]=heap[heapSize-1];
    heapSize--;
    heapifyDown(0);
}
//deletion at any index(middle)
void deleteAtIndex(int i) {

    if (heapSize == 0) {
        cout << "heap is empty";
        return;
    }

    if (i < 0 || i >= heapSize) {
        cout << "invalid index";
        return;
    }

    heap[i] = heap[heapSize - 1];
    heapSize--;

    if (i > 0 && heap[i] < heap[(i - 1) / 2])
        heapifyUp(i);
    else
        heapifyDown(i);
}

int main() {

insert(10);
insert(20);
insert(1);
insert(0);
deleteMin();
deleteAtIndex(2);

for(int i =0;i<heapSize;i++) cout<<heap[i]<< " ";

}	