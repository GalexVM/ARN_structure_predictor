#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>
using namespace std;

void initializeMatrix(vector<int>& mat);
void calculate(vector<int>& mat,  vector<vector<pair<int,int>>>& mat2);
int getMinValue(vector<int>& mat, int f, int c, function<int(char,char)> energy, char ri, char rj, vector<pair<int,int>>& mincoords);
int energyFunction1(char ri, char rj);
int energyFunction2(char ri, char rj);
void printMatrix(vector<int>& mat);

string cadena;
int main(){
    cadena = "GGAAAUCC";
    vector<int> mainMatrix = vector<int>(cadena.length()*cadena.length(),100);
    vector<vector<pair<int,int>>> precedArrowMatrix = vector<vector<pair<int,int>>>
                                (cadena.length()*cadena.length(),vector<pair<int,int>>());
    initializeMatrix(mainMatrix);
    printMatrix(mainMatrix);
    calculate(mainMatrix, precedArrowMatrix);
    printMatrix(mainMatrix);
}
int getMinValue(vector<int>& mat, int f, int c, function<int(char,char)> energy,
                 char ri, char rj, vector<pair<int,int>>& mincoords){
    int size = sqrt(mat.size());
    vector<int> values;
    values.push_back(mat[size*(f+1)+(c-1)] + energy(ri,rj)); //E(i+1,j-1)+a(i,j)
    values.push_back(mat[size*f+(c-1)]); //E[i,j-1]
    values.push_back(mat[size*(f+1)+c]); //E(i+1,j)
    
    int k = f+1;
    if(abs(f-c)>1){
        vector<int>subvalues;
        for(int x = 0; x < abs(f-c); x++)
            subvalues.push_back(mat[size*f+(f+x)]+mat[size*(f+x+f)+c]); //E[i,k]+E[k+i,j]
        auto temp = min_element(subvalues.begin(),subvalues.end());
        values.push_back(*temp);
        for(int x = 0; x < abs(f-c); x++){
            if(temp == subvalues.begin()+x){
                k = x;
            }
        }
    }
    auto m = min_element(values.begin(),values.end());
    if(m == values.begin()+1){
        mincoords.emplace_back(f,c-1);}
    else if(m == values.begin()+2){
        mincoords.emplace_back(f+1,c);}
    else if(m == values.begin()){
        mincoords.emplace_back(f+1,c-1);}
    else if(m == values.end() && values.end() != values.begin()+2){
        mincoords.emplace_back(f,f+k);
        mincoords.emplace_back(f+k+f,c);
    }
    return *m;
}
void calculate(vector<int>& mat,  vector<vector<pair<int,int>>>& mat2){
    vector<pair<int,int>> predCoords;
    int size = sqrt(mat.size());
    for(int x = 1; x < size; x++){
        for(int i = 0; i < size-x; i++){
            mat[size*i+(i+x)] = getMinValue(mat,i,i+x,energyFunction2,cadena[i],cadena[i+x], predCoords);
            mat2[size*i+(i+x)] = predCoords;
            predCoords.clear(); 
        }
    }
}
void initializeMatrix(vector<int>& mat){
    int size = sqrt(mat.size());
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(i == j || j == (i-1))
                mat[size*i +j] = 0;
}
int energyFunction1(char ri, char rj){
    if((ri == 'C' && rj == 'G') || (ri == 'G' && rj == 'C')) return -5;
    if((ri == 'A' && rj == 'U') || (ri == 'U' && rj == 'A')) return -4;
    if((ri == 'G' && rj == 'U') || (ri == 'U' && rj == 'G')) return -1;
    else{return 0;}
}
int energyFunction2(char ri, char rj){
    if((ri == 'C' && rj == 'G') || (ri == 'G' && rj == 'C')) return -1;
    if((ri == 'A' && rj == 'U') || (ri == 'U' && rj == 'A')) return -1;
    else{return 0;}
}
void printMatrix(vector<int>& mat){
    int size = sqrt(mat.size());
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << mat[size*i+j] <<'\t';
        }cout << endl;
    }cout<<endl;
}