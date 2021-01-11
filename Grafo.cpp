#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

int matriz[10][10],pai[10];

int i=0, j=0, vertices, arestas, x, y, z, a, b, sinal, atual, custo,opcao;
deque<int> avisitar, visitados;

int main()
{
   ifstream arquivo;
   
   cout <<  "\n 1 - Grafo";
   cout <<  "\n 2 - Digrafo \n Opcao: ";
   cin >> opcao;
   
   switch(opcao)
   {
	case 1:
		arquivo.open("grafo0.txt");
   		arquivo >> vertices >> arestas;
   
	   	for(i=0; i<arestas; i++)    // atribuir nós e custos
		   {  
		      arquivo >> x >> y >> z;
		      matriz[x][y] = z;
		      matriz[y][x] = z;
		   }
		   cout << "\n";   
	break;
	case 2:
		arquivo.open("grafo1.txt");
  		arquivo >> vertices >> arestas;
		for(i=0; i<arestas; i++)    // atribuir nós e custos
		   {  
		      arquivo >> x >> y >> z;
		      matriz[x][y] = z;
		   }
		   cout << "\n";      
   }
	   

   for(i=1; i<vertices+1; i++) //imprimir matriz
   {
      for(j=1; j<vertices+1; j++)
         cout << matriz[i][j] << " ";
      cout << "\n";   
   }
   cout << "\nDigite no 1: "; cin >> a;
   cout << "\nDigite no 2: "; cin >> b;  
   
   avisitar.push_front(a);

   while(!avisitar.empty()==1)
   {
      atual = avisitar.back();
      avisitar.pop_back();
      visitados[atual] = 1;
      
      if(atual == b)
      {
         sinal = 1;
         break;
      }
      

      for(i=0; i<=vertices; i++)    //insere os vizinhos de atual
      {
         if(!matriz[atual][i]==0 and visitados[i]==0)
         {
            avisitar.push_front(i);
            visitados[i] == 1;
            pai[i] = atual;
            custo++;
         }
         
      }
     
   }
   
    if(sinal == 1)
	{
		i = b;
   		cout << "\n Conectados: " << i << " ";
   		while(pai[i]!=0)
   		{
			cout << pai[i] << " ";
		    i = pai[i];
		}
		cout << "\n Custo: " << custo;
	}
	else
		cout << "\n Nao conectados";
   		

   return 0;
}
