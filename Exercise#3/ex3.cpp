#include <iostream>
#define MAX 10e9
using namespace std;

int main()
{
    int n=0;
    int m=0;
    cin >> n >> m;
    
    int profit[n][m+1];
    for(int i=0; i<n; i++){
        for(int j=0; j<m+1; j++){
            cin >> profit[i][j];
        }
    }
    
    int current_count[m+1][m+1];
    int temp_max[m+1];
    
    //Initialize
    for(int i=0; i<m+1; i++){
        temp_max[i] = 0;
        for(int j=0; j<m+1; j++)
            current_count[i][j] = 0;
    }
    
    int idx[m+1];
    int temp;
    int count=0;
    
    for(int i=0; i<n; i++){
        
        //stage 1
        if(i==0){
            for(int j=0; j<m+1; j++)
                idx[j] = profit[0][j];
        }
        
        //other
        else{
            for(int j=0; j<m+1; j++){
                for(int k=0; k<m+1; k++){
                    temp = profit[i][j] + idx[k];
                    count = j+k;
                    if(count>m)
                        break;
                    else
                        current_count[j][k] = temp;
                    if(current_count[j][k]>temp_max[j+k])
                        temp_max[j+k] = current_count[j][k];
                }
            }

            for(int i=0; i<m+1; i++){
                if(temp_max[i]>idx[i])
                    idx[i] = temp_max[i];
            }
        }
    }

    int max=0;
    for(int i=0; i<m+1; i++){
        if(idx[i] > max)
            max = idx[i];
    }

    cout << max;
}
