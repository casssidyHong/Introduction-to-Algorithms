#include <iostream>

using namespace std;

int main(){
    
    int n;
    int key;
    int arr[10005] = {0};
    
    //cout << "Please enter the number of coins: ";
    while(cin >> n){
        //cin >> n;
        key = 0;
        
        if(n>1000 || n<3){
            cout << "error\n";
            continue;
        }
        //cout << "\n Please enter the weights of coins: ";
        for(int i=1; i<n+1; i++){
            cin >> arr[i];
            if(arr[i]<0){
                cout << "error\n";
                continue;
            }
        }
        
        int k = 0;
        
        //ans is not the first or the last
        if(arr[1]!=arr[2] && arr[1]!=arr[3]){
            cout << "0" << endl;
            continue;
        }
        else if(arr[n]!=arr[n-1] && arr[n]!=arr[n-2]){
            cout << n-1 << endl;
            continue;
        }
        
        if(n%3 == 0)
            k = n;
        else if(n%3 == 1){
            k = n-1;
        }
        else
        {
            if(arr[n] == arr[n-1]){
                k = n-2;
            }
            else{
                if(arr[n] == arr[n-2]){
                    cout << n-2 << endl;
                    continue;
                }
                else{
                    cout << n-1 << endl;
                    continue;
                }
            }
        }
        
        
        int x = 1;
        int sum1 = 0;
        int sum2 = 0;
        int sum3 = 0;
        
        while(x != k){
            //cout << "k = " << k << endl;
            //cout << "x = " << x << endl;
            
            for(int i=x; i<k/3+1; i++){
                sum1 = sum1 + arr[i];
            }
            for(int i=k/3+1; i<2*k/3+1; i++){
                sum2 = sum2 + arr[i];
            }
            for(int i=2*k/3+1; i<k+1; i++){
                sum3 = sum3 + arr[i];
            }
            //sum1 is different
            if(sum2 == sum3){
                x = 1;
                k = k/3;
            }
            //sum2 is different
            else if(sum1 == sum3){
                x = k/3 + 1;
                k = 2*k/3;
            }
            //sum3 is different
            else{
                x = 2*k/3 + 1;
                k = k;
            }
            if(x == k){
                break;
            }
            if(k == x+1){
                //x is correct
                //ans is not the first or the last
                if(arr[x] == arr[x-1] && arr[x] == arr[k+1]){
                    cout << k-1 << endl;
                    key = 1;
                    break;
                }
            }
        }
        if(key==0)
            //cout << "k = " << k <<endl;
            cout << x-1 << endl;
        //continue;
    }
    
    return 0;
}
