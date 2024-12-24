#include <iostream>
#include <vector>
using namespace std;

int main(){

    int n;
    cin>>n;
    vector<bool> prost(n+1, true);
    prost[0] = false; prost[1] = false;

    for(int i = 2; i*i <= n; i++){
        if(prost[i]){
            for(int j = i*i; j <= n; j += i){
                prost[j] = false;
            } 
        }
    }
    for(int i = 2; i < prost.size(); i++){
        if(prost[i]) cout<<i<<" ";
    }

    return 0;
}