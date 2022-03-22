#include <iostream>
using namespace std;
int main(){

    char MAPA[31][51] = {0};

    for(int i = 0; i<31; i ++){
        for(int j= 0; j<51; j++){
            
            if(i == 0 || i == 30 || j == 0 || j == 50){
                MAPA[i][j] = '1';
            }
            else if(i >= 11 && i <= 16){
                if(j<=31){
                    MAPA[i][j] = '2';
                }
                else{
                    MAPA[i][j] = '0';
                }
            }
            else if(i >= 17 && i <= 22){
                if(j >= 24){
                    MAPA[i][j] = '2';
                }
                else{
                    MAPA[i][j] = '0';
                }
            }
            else{
                MAPA[i][j] = '0';
            }
        }
    }
    for(int i = 0; i<31; i ++){
        cout << "\"";
        for(int j= 0; j<51; j++){
            cout << MAPA[i][j];
        }
        cout << "\",";
        cout << endl;
    }

    return 0;
}