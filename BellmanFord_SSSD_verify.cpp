#include <iostream>
#include <cstdlib>
#include <ctime>

#include "mc_scverify.h"

static const int N = 6;

#pragma hls_design top
void CCS_BLOCK(BellmanFord)(short adj[N][N], short start, short paths[N], bool &valid_result){
  bool flag = 0; 
  valid_result = 0; 
  
  SWAP:if(start != 0){
    for(int i = 0; i < N; i++){ //swap first row and start row
      int a = adj[start][i];
      int b = adj[0][i];
      a = a + b;
      b = a - b;
      adj[start][i] = a - b;
      adj[0][i] = b;
    }
  }
  
  K:for(int k = 0; k < N - 1; k++){ 
    if(!flag){
      flag = 1;
      I:for(int i = 0; i < N; i++){
        int vert_i = paths[i];
        J:for(int j = 0; j < N; j++){
          int weight = adj[i][j];
          if( weight != 0 && (vert_i + weight) < paths[j] && vert_i != 1000){
            paths[j] = vert_i + weight;
            flag = 0;
          }
        }
      }
    }else if(flag){ 
      continue; 
    }
  }
  
  NI:for(int i = 0; i < N; i++){
    short vert_i = paths[i];
    NJ:for(int j = 0; j < N; j++){
      short weight = adj[i][j];
      if(weight != 0 && paths[j] > (vert_i + weight) && vert_i != 1000){
        //std::cout << "There is a Negative Cicle. No shortest path can be calculated." << std::endl;
        valid_result = 1;
      }
    }
  }

}

//********testbench********
CCS_MAIN(int argc, char* argv[]){

    std::srand(std::time(NULL));

                /*                          End of iteration k:
                {0, 10, 0, 0, 0, 8}         k == 0: {0, 10, 10, 12, 9, 8}
                {0, 0, 0, 2, 0, 0}          k == 1: {0, 5, 10, 8, 9, 8}
                {0, 1, 0, 0, 0, 0}          k == 2: {0, 5, 5, 7, 9, 8}
                {0, 0, -2, 0, 0, 0}         k == 3: {0, 5, 5, 7, 9, 8}
                {0, -4, 0, -1, 0, 0}        k == 4: {0, 5, 5, 7, 9, 8}
                {0, 0, 0, 0, 1, 0}          k == 5: {0, 5, 5, 7, 9, 8}
                */

    short a[N][N] = {{0, 10, 0, 0, 0, 8}, {0, 0, 0, 2, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 0, -2, 0, 0, 0}, {0, -4, 0, -1, 0, 0}, {0, 0, 0, 0, 1, 0}};
    short G[N][N], randNum, start;
    bool valid;
    
    //Random verification tests
    for(int k = 0; k < 100; k++){
        short paths[N] = {0, 1000, 1000, 1000, 1000, 1000};
        start = rand() % N;
        
        //Create random matrix G 
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                randNum = (std::rand() % 40);
                if(i == j || randNum < -10 || randNum > 10){
                    randNum = 0;
                }
                G[i][j] = randNum;
                std::cout << G[i][j] << " ";
            }
            std::cout << std::endl;
        }
        
        //Execute SP Alg
        BellmanFord(G, start, paths,valid);
        
        //Print results
        std::cout << "Is valid: " << valid << std::endl; 
        
        for(int i = 0; i < N; i++){
            std::cout << paths[i] << " "; 
        }
    std::cout << std::endl;
    }
    
    //Matrix A 
    
    //Print matrix A
    for(int k = 0;k<N;k++){
      for(int j = 0;j<N;j++){
        std::cout << a[k][j] << " ";
      }
      std::cout << std::endl;
    }
    short paths[N] = {0,1000,1000,1000,1000,1000};
    
    //Execute alg for matrix A
    BellmanFord(a,0,paths,valid);
    
    //Print Results of matrix A
    std::cout << "Is valid: " << valid << std::endl; 
        
    for(int i=0;i<N;i++){
      std::cout << paths[i] << " "; 
    }
    std::cout << std::endl;
    
    CCS_RETURN(0);
}
