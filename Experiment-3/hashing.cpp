// Experiment 3- Finds the length of the longest contiguous subarray with equal number of P and A
#include<iostream>
#include<unordered_map>
using namespace std;
int main(){
    int N;
    cin>>N;
    char arr[N];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    unordered_map<int , int>mp; // pair= sum,index
    int sum=0;
    int maxlen=0;
    mp[0]=-1;
    int i;
    for(i=0;i<N;i++){
        if (arr[i]== 'P')
        sum+=1;
        else
        sum-=1;
    
    if (mp.find(sum)!=mp.end()){
        int l= i- mp[sum];
        if(l>maxlen){
            maxlen=l;
        }
    }
    else{
        mp[sum]=i;
    }
    }
    cout<<maxlen;
    return 0;

}
