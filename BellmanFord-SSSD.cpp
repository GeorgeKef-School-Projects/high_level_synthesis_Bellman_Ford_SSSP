#include <iostream>
#include <ctime>

static const int N = 6;

void BellmanFord(int adj[N][N], int start, int (&paths)[N]){
    bool flag = 0; 

    if(start != 0){
      for(int i = 0; i < N; i++){ //swap first row and start row
        adj[start][i] = adj[start][i] + adj[0][i];
        adj[0][i] = adj[start][i] - adj[0][i];
        adj[start][i] = adj[start][i] - adj[0][i];
      }
    }

    for(int k = 0; k < N - 1; k++){ 
        
	if(!flag){
	  flag = 1;
	  for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
              if( adj[i][j] != 0 && (paths[i] + adj[i][j]) < paths[j] && paths[i] != 1000){
                paths[j] = paths[i] + adj[i][j];
	        flag = 0;
              }
            }
          }
    	}else if(flag){ 
	  continue; 
	}
    }

    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        if(adj[i][j] != 0 && paths[j] > (paths[i] + adj[i][j]) && paths[i] != 1000){
	  std::cout << "There is a Negative Cicle. No shortest path can be calculated." << std::endl;
	}
      }
    }

}

//********testbench********
int main(){

    srand(time(NULL));

                /*                          End of iteration k:
                {0, 10, 0, 0, 0, 8}         k == 0: {0, 10, 10, 12, 9, 8}
                {0, 0, 0, 2, 0, 0}          k == 1: {0, 5, 10, 8, 9, 8}
                {0, 1, 0, 0, 0, 0}          k == 2: {0, 5, 5, 7, 9, 8}
                {0, 0, -2, 0, 0, 0}         k == 3: {0, 5, 5, 7, 9, 8}
                {0, -4, 0, -1, 0, 0}        k == 4: {0, 5, 5, 7, 9, 8}
                {0, 0, 0, 0, 1, 0}          k == 5: {0, 5, 5, 7, 9, 8}
                */

    int a[N][N] = {{0, 10, 0, 0, 0, 8}, {0, 0, 0, 2, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 0, -2, 0, 0, 0}, {0, -4, 0, -1, 0, 0}, {0, 0, 0, 0, 1, 0}};
    int G[N][N], randNum, start;
    for(int k = 0; k < 10; k++){
        int paths[N] = {0, 1000, 1000, 1000, 1000, 1000};
        start = rand() % N;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                randNum = (rand() % 40);
                if(i == j || randNum < -10 || randNum > 10){
                    randNum = 0;
                }
                G[i][j] = randNum;
                std::cout << G[i][j] << " ";
            }
            std::cout << std::endl;
        }
        BellmanFord(G, start, paths);
        for(int i = 0; i < N; i++){
            std::cout << paths[i] << " "; 
        }
	std::cout << std::endl;
    }
    for(int k = 0;k<N;k++){
      for(int j = 0;j<N;j++){
        std::cout << a[k][j] << " ";
      }
      std::cout << std::endl;
    }
    int paths[N] = {0,1000,1000,1000,1000,1000};
    BellmanFord(a,0,paths);
    for(int i=0;i<N;i++){
      std::cout << paths[i] << " "; 
    }
    std::cout << std::endl;
    
    return 0;
}
