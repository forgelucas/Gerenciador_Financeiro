#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Registro
{
  int mes;
  int ano;
  float valor;
  float moradia;
  float estudos;
  float trans;
  float ali;
  float invest;
  float selic;
};

struct Registro registro;
float meses_lucro[13];

char meses[12][0xFF] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro","Dezembro"};

//1- Cadastro de Receitas e Gastos
int cadrg(){//Cadastro receita e gasto
  printf("Digite o mês e o ano: ");
  scanf("%d",&registro.mes);
  scanf("%d",&registro.ano);
  printf("Insira o valor depositado: ");
  scanf("%f",&registro.valor);
  printf("gasto com moradia: ");
  scanf("%f",&registro.moradia);
  printf("gasto com estudos: ");
  scanf("%f",&registro.estudos);
  printf("gasto com transporte: ");
  scanf("%f",&registro.trans);
  printf("gasto com alimentação: ");
  scanf("%f",&registro.ali);
  puts("");

 meses_lucro[registro.mes] = registro.valor-(registro.moradia+registro.estudos+registro.trans+registro.ali);
  
  FILE *file;
  file=fopen("MYGF/index.html","a");
  
  if (file==NULL){
    printf("O arquivo não existe!");
    getchar();
    exit(0);
  }
  fprintf(file, "DATA: %d/%d\n",registro.mes,registro.ano);
  fprintf(file, "Valor: R$ %.2f\n",registro.valor);
  fprintf(file, "Moraida: R$ %.2f\n",registro.moradia);
  fprintf(file, "Estudos: R$ %.2f\n",registro.estudos);
  fprintf(file, "Transporte: R$ %.2f\n",registro.trans);
  fprintf(file, "Alimentação: R$ %.2f\n",registro.ali);
  fprintf(file, "Lucro do mês: R$ %.2f\n",meses_lucro[registro.mes]);
  fprintf(file,"---------------------------------\n");

  fclose(file);
  return 0;
}

//2-Relatório de Movimentação dos Ultimos 12 Meses
int anual(){//Registro anual dos gastos
  float lucro_anual;
  if(registro.selic != 0)
  {
    meses_lucro[registro.mes] = registro.valor-(registro.moradia+registro.estudos+registro.trans+registro.ali)+registro.selic;
  }
  else
  {
    meses_lucro[registro.mes] = registro.valor-(registro.moradia+registro.estudos+registro.trans+registro.ali);
  }
  for (int i = 1; i <= 12; i++) {
  lucro_anual += meses_lucro[i];
  printf("%s %s\t= R$ %.2f\n",meses[i-1], (i>=3 && i<=8) ? "\t" : ""  ,meses_lucro[i]);
  }

  printf("\nO seu lucro anual foi de: R$ %.2f\n",lucro_anual);
  //HTML Relatorio anual
  FILE *file;
  file=fopen("MYGF/anual.html","a");
  for (int i = 1; i <= 12; i++) 
  {
  lucro_anual += meses_lucro[i];
  fprintf(file,"%s %s\t= R$ %.2f\n",meses[i-1], (i>=3 && i<=8) ? "\t" : ""  ,meses_lucro[i]);
  }
  fprintf(file,"\nO seu lucro anual foi de: R$ %.2f\n",lucro_anual);
  
  return 0;
} 

//3-Relatório do ultimo mes
int ultmes(){//Registro anual dos gastos
  meses_lucro[registro.mes] = registro.valor-(registro.moradia+registro.estudos+registro.trans+registro.ali)+registro.selic;

  FILE *file;
  file=fopen("MYGF/index.html","a");
  printf("MOVIMENTAÇÃO DO ÚLTIMO MÊS\n");
  puts("");
  printf("DATA: %d/%d\n",registro.mes,registro.ano);
  printf("Valor: R$ %.2f\n",registro.valor);
  printf("Moraida: R$ %.2f\n",registro.moradia);
  printf("Estudos: R$ %.2f\n",registro.estudos);
  printf("Transporte: R$ %.2f\n",registro.trans);
  printf("Alimentação: R$ %.2f\n",registro.ali);
  printf("Lucro do mês: R$ %.2f\n",meses_lucro[registro.mes]);
  fclose(file);
  return 0;
} 

//Investimento selic
int invest(){

  printf("Bem vindo ao seu investimento! \n");
  printf("---------------------------------\n");  
  
    printf("Digite o mês e o ano: ");
    scanf("%d",&registro.mes);
    scanf("%d",&registro.ano);
    
    printf("O seu saldo este mes é de: %.2f \n", meses_lucro[registro.mes]);

    printf("Qual valor deseja depositar? ");
    scanf("%f", &registro.invest);

    if(registro.mes == 1 || registro.mes == 2)
    {
      registro.selic = registro.invest * 1.008;
    }
    else if(registro.mes == 3 || registro.mes == 4)
    {
      registro.selic = registro.invest * 1.018;
    }
    else if(registro.mes == 5 || registro.mes == 6)
    {
      registro.selic = registro.invest * 1.015;
    }
    else if(registro.mes == 7 || registro.mes == 8)
    {
      registro.selic = registro.invest * 1.019;
    }
    else if(registro.mes == 9 || registro.mes == 10)
    {
      registro.selic = registro.invest * 1.012;
    }
    else if(registro.mes == 11 || registro.mes == 12)
    {
      registro.selic = registro.invest * 1.006;
    }
    
    printf("Valor rendido dno investimento do mês: ");
    printf("%.2f\n",registro.selic);

    FILE *file;
    file=fopen("MYGF/invest.html","a");
    fprintf(file,"Valor rendido no investimento do mês %d e ano %d é de: ", registro.mes, registro.ano);
    fprintf(file,"%.2f\n",registro.selic);
    fprintf(file,"---------------------------------\n");
    fclose(file);
    return 0;
}

//chamando o menu de volta
void retorno();

int main(void){

  puts("--------------------------------------------------");
  puts("$$$\\    $$$ |\\$$\\   $$  |   $$  __$$\\ $$  _____| ");
  puts("$$$$\\  $$$$ | \\$$\\ $$  /    $$ /  \\__|$$ |       ");
  puts("$$\\$$\\$$ $$ |  \\$$$$  /     $$ |$$$$\\ $$$$$\\     ");
  puts("$$ \\$$$  $$ |   \\$$  /      $$ |\\_$$ |$$  __|    ");
  puts("$$ |\\$  /$$ |    $$ |       $$ |  $$ |$$ |       ");
  puts("$$ | \\_/ $$ |    $$ |       \\$$$$$$  |$$ |       ");
  puts("\\__|     \\__|    \\__|        \\______/ \\__|       " );
  
  printf("\n");
  puts("Ola, seja bem vindo M.Y.G.F!");
  puts("Seu Gerenciador Financeiro.");
  puts("Aproveite o nosso software!");
  puts("Por favor, escolha uma opção.");
  printf("--------------------------------------------------\n"
  "1-Cadastro de Receitas e Gastos\n"
  "2-Relatório de Movimentação dos Ultimos 12 Meses\n"
  "3-Relatório de Cada Categaoria (último mês)\n"
  "4-Investir\n"
  "5-Integrantes\n"
  "--------------------------------------------------\n");
  
  int opc;
  printf("Digite a opção escolhida: ");
  scanf("%d",&opc);
  puts("\n");

  switch (opc)
  {
    case 1:
    cadrg();
    
    break;
    case 2:
    anual();
    
    break;
    case 3:
    ultmes();
    break;
    case 4:
    invest();
    break;
    case 5:
    puts("Lucas Forge Freo - CEO");
    
    puts("");
    puts("João Lucas Freitas de Almeida Rocha - CTO");
    
    break;
  };
  retorno();
}

//Função de retorno p/ o menu.  
void retorno(){
  int confirm;
  puts("--------------------------------------------------\n");
  printf("Digite 0 para voltar ao menu: ");
  scanf("%d",&confirm);
  puts("");
  if(confirm==0){
    main();
  }
}
 