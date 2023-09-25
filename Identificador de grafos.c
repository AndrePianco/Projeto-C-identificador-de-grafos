#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

void criar_grafo(int tam, int matriz[tam][tam]);
void identificar_ligacoes(int tam, int matriz[tam][tam]);
void imprimir_ligacoes(int tam, int matriz[tam][tam]);
void menu(int tam, int grafo[tam][tam]);

void completo(int tam, int grafo[tam][tam]);
void multigrafo(int tam, int grafo[tam][tam]);
void lacos(int tam, int grafo[tam][tam]);
void folhas(int tam, int grafo[tam][tam]);
void isolado(int tam, int grafo[tam][tam]);
void planar(int tam, int grafo[tam][tam]);

void pausarTela();
int direcionado;

int main()
{
  int quantVertices;
  printf("- Matriz de adjacências -\n\n");
  printf("Informe quantos vertices tem o grafo: ");
  scanf("%d", &quantVertices);
  int grafo[quantVertices][quantVertices];
  printf("Digite 0 para grafo não direcionado e 1 para direcionado: ");
  scanf("%d",&direcionado);
  criar_grafo(quantVertices,grafo);
  identificar_ligacoes(quantVertices,grafo);
  menu(quantVertices,grafo);
}

void criar_grafo(int tam, int matriz[tam][tam])
{
  for (int i = 0; i < tam; i++)
  {
    for (int j = 0; j < tam; j++)
    {
      matriz[i][j] = 0;
    }
  }
}

void identificar_ligacoes(int tam, int matriz[tam][tam])
{
  for (int i = 0; i < tam; i++)
  {
    int nl;
    printf("\nQuantas ligacoes temos no vertice %d? ", i);
    scanf("%d", &nl);
    for (int j = 0; j < nl; j++)
    {
      int ligacao;
      printf("Informe a %da ligacao do vertice %d: ", j + 1, i);
      scanf("%d", &ligacao);
      if (ligacao >= 0 && ligacao < tam && direcionado == 0)
      {
          matriz[i][ligacao] += 1;
          matriz[ligacao][i] = matriz[i][ligacao];
      }
      else if(ligacao >= 0 && ligacao < tam && direcionado == 1)
      {
          matriz[i][ligacao] += 1;
      }
      else
      {
        printf("Ligacao invalida!\n");
        j--;
      }
    }
  }
}

void imprimir_ligacoes(int tam, int matriz[tam][tam])
{
    printf("\nMatriz de adjacências: \n\n");
    for(int i = 0;i < tam;i++)
    {
        for(int j = 0;j < tam;j++)
        {
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void menu(int tam, int grafo[tam][tam])
{
    int contador = 1;
    int opcao;
    system(CLEAR_SCREEN);
    while(contador != 0)
    {
        printf("##BEM VINDO AO PROGRAMA DE CARACTERISTICAS DE GRAFOS##\n");
        imprimir_ligacoes(tam,grafo);
        printf("Escolha a sua opção: \n0 - Sair\n1 - Verificar se o grafo é completo\n2 - Verificar se é um multigrafo\n3 - Quantos laços existem?\n4 - Quantos vértices folhas existem?\n5 - Verificar se existe vértice isolado\n6 - Verificar se é possível ser planar\nInforme o comando:");
        scanf("%d",&opcao);
        switch(opcao)
        {
            case 0:
                contador = 0;
                break;
            case 1:
                completo(tam,grafo);
                break;
            case 2:
                multigrafo(tam,grafo);
                break;
            case 3:
                lacos(tam,grafo);
                break;
            case 4:
                folhas(tam,grafo);
                break;
            case 5:
                isolado(tam,grafo);
                break;
            case 6:
                planar(tam,grafo);
                break;
            default:
                printf("\nNúmero Inválido!\n");
                pausarTela();
        }
        system(CLEAR_SCREEN);
    }
    printf("Programa encerrado!");
   
}

void lacos(int tam, int grafo[tam][tam])
{
    int quant = 0;
    for (int i = 0; i< tam; i++)
    {
        if (grafo[i][i] != 0){
            quant += grafo[i][i];
        }
    }
    printf("Quantidade de laços do grafo: %d\n\n",quant);
    pausarTela();
}

void isolado(int tam, int grafo[tam][tam]){
    int quant = 0;
    int isolados = 0;
    for (int i = 0; i < tam; i++)
    {
        int quant = 0;
        for (int j = 0; j < tam; j++)
        {
            quant = quant + grafo[i][j];
        }
        for(int u = 0; u < tam; u++)
        {
            quant = quant + grafo[u][i];
        }
        if (quant == 0)
        {
            isolados++;
        }
    }
    printf("Quantidade de vertices isolados: %d\n\n",isolados);
    pausarTela();
}

void folhas(int tam, int grafo[tam][tam]){
    int folhas = 0;
    if (direcionado == 1)
    {
        for (int i = 0; i < tam; i++)
        {
            int quant = 0;
            for (int j = 0; j < tam; j++)
            {
                quant = quant + grafo[i][j];
            }
            for(int u = 0; u < tam; u++)
            {
                quant = quant + grafo[u][i];
            }
            if (quant == 1)
            {
                folhas++;
            }
        }
    }
    else
    {
        for (int i = 0; i < tam; i++)
        {
            int quant = 0;
            for (int j = 0; j < tam; j++)
            {
                quant = quant + grafo[i][j];
            }
            if (quant == 1)
            {
                folhas++;
            }
        }
    }
    printf("Quantidade de vertices folhas: %d\n\n",folhas);
    pausarTela();
}

void multigrafo(int tam, int grafo[tam][tam])
{
    int quant = 0;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if(grafo[i][j] >= 2){
                quant++;
            }
        }
    }
    if (quant > 0){
        printf("É multigrafo!\n\n");
    } else {
        printf("Não é um multigrafo!\n\n");
    }
    pausarTela();
}



void planar(int tam,int grafo[tam][tam])
{
    int Arestas = 0;
    int formula = (3*tam) - 6;
    if (direcionado ==  1)
    {
        for(int i = 0; i < tam; i++)
        {
            for(int j = 0; j < tam; j++)
            {
                Arestas = Arestas + grafo[i][j];
            }
        }
    }
    else
    {  
        for(int i = 0; i < tam; i++)
        {
            for(int j = 0; j < tam; j++)
            {
                if(i < j || i == j)
                {
                    Arestas = Arestas + grafo[i][j];
                }
            }
        }
    }
    if(Arestas <= formula)
    {
        printf("O grafo pode ser planar!\n\n");
    }
    else
    {
        printf("O grafo não é planar!\n\n");
    }
    pausarTela();
}

void completo(int tam, int matriz[tam][tam])
{
    int completo = 1;

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (i != j && matriz[i][j] != 1)
            {
                completo = 0; 
                break;
            }
        }
    }

    if (completo)
    {
        printf("\nÉ completo!\n\n");
    }
    else
    {
        printf("\nNão é completo!\n\n");
    }
    pausarTela();
}

void pausarTela(){
    getchar();
    if (strcmp(CLEAR_SCREEN,"cls") == 0){ //condicao para pausar a tela no windows
        system("pause");
    } else if (strcmp(CLEAR_SCREEN,"clear") == 0){ //em sistemas baseados em UNIX(ex: Linux)
        printf("Pressione Enter para continuar...");
        getchar();
    }
}