#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
//
typedef struct T_Arquivo{
	int trade,modo,key;
	char Jogo[3][3];
                        }Arquivo;
void New_Game(FILE *arq);//OK
void Continue_Game(FILE *arq);
void Desafio_Maquina(FILE *arq,int trade,char preenchimento);//OK
void PvP(FILE *arq,int *trade,char preenchimento);//OK
void Printar_Jogo(char Jogo[3][3]);
int Win_Cond(char Jogo[3][3]);
void Salvar_Jogo(FILE *arq,int trade,int modo,char Jogo[3][3],int key);//OK//key é Ativar logicamente uma vez criado o arquivo salve numca sera deletado fisicamente
void Modo_Facil(FILE *arq,int *trade,char preenchimeto);
void Modo_Medio(FILE *arq,int *trade,char preenchimeto);
void Modo_Dificil(FILE *arq,int *trade,char preenchimeto);


int main(){
	char op;
	FILE *arq;


	do{
			arq=fopen("Salve","r+b");
	if(arq==NULL){
		arq=fopen("Salve","w+b");
	             }
		system("cls");
		printf("\n\t--JOGO DA VELHA--\n");
		printf("1_Novo Jogo\n2_Continuar\n3_Sair\nOpcao: ");
		fflush(stdin);
		scanf("%c",&op);
		fflush(stdin);

	switch(op){
	case'1':
		New_Game(arq);
		break;
	case'2':
		Continue_Game(arq);
		break;
	case'3':
		break;
	default:
		printf("\nOpcao Invalida!!");
	          }
 	    }while(op!='3');


system("pause");
return 0;
           }



void New_Game(FILE *arq){
	int trade;
	char op;
	system("cls");
		printf("\n\tNOVO JOGO\n");
	do{
		printf("\n1_Contra a Maquina\n2_Partida Amistosa\n3_sair\nOpcao: ");
		fflush(stdin);
		scanf("%c",&op);
		fflush(stdin);
		switch(op){
		case'1':
			srand( (unsigned)time(NULL) );
	        trade=rand()%2;
			Desafio_Maquina(arq,trade,'n');
			return;
			break;
		case'2':
			srand( (unsigned)time(NULL) );
	        trade=rand()%2;
			PvP(arq,&trade,'n');
			return;
			break;
		case'3':
			break;
		default:
			printf("\nOpcao invalida!!");
			break;
		          }
	  }while(1);
                        }



void PvP(FILE *arq,int trade,char preenchimento){        //o preenchimento'n' é para novo jogo e o 'c' é para o continue
	Arquivo Servo;
	int tradelocal=trade,l,c,ok=0,salve=0,i,j;
	char player1[25],player2[25];
	char Jogo[3][3];
	if(preenchimento=='n'){
		for(i=0;i<3;i++){
			for(j=0;i<3;j++){
				Jogo[i][j]=' ';
			                }
		                }
	                      }
	else{
		fseek(arq,0,0);
		fread(&Servo,sizeof(Arquivo),1,arq);
		fseek(arq,0,0);
		for(i=0;i<3;i++){
			for(j=0;i<3;j++){
				Jogo[i][j]=Servo.Jogo[i][j];
			                }
		                }
	    }
	printf("\nInforme o Nome do Jogador 1 'X': ");
	fgets(player1,25,stdin);
	printf("\nInforme o Nome do Jogador 2 'O': ");
	fgets(player2,25,stdin);
	
	if(tradelocal==0){
		printf("\n\t%s Comeca!!",player1);
	            }
	else
		printf("\n\t%s Comeca!!",player2);
	do{
	printf("\n\tPartida Amistosa\n");  //Falta Implementar o Ctrl S
	
	do{
	Printar_Jogo(Jogo);
	do{
	printf("\nInforme a Linha em que Deseja Inserir 'X' ou 'O': ");
	scanf("%d",&l);
	switch(l){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
	  }while(l!=0&&l!=1&&l!=2);

do{
	printf("\nInforme a Coluna em que Deseja Inserir : ");
	scanf("%d",&c);
	switch(c){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
   }while(c!=0&&c!=1&&c!=2);    //valida coluna
if(Jogo[l][c]==' '){
	ok=1;
	
	if(tradelocal==0){
		Jogo[l][c]='X';
		if(Win_Cond(Jogo)==1){
			printf("\nO Jogador %s Venceu!!",player1);
			return;
		                     }
		system("cls");
	tradelocal=1;
	printf("Vez de %s",player2);
	            }
	else{
		Jogo[l][c]='O';
		if(Win_Cond(Jogo)==1){
			printf("\nO Jogador %s Venceu!!",player2);
			return;          }
		system("cls");
		tradelocal=0;
		printf("Vez de %s",player1);
	    }
                   }
else{
	printf("\nEssa Posiçao Ja foi Ocupada!! ");
	system("cls");
    }
	}while(ok!=1);              //valida se a estiver desocupada
	  }while(1);                // intercalaçao dos jogadores
                   }



void Salvar_Jogo(FILE *arq,int trade,int modo,char Jogo[3][3],int key){
	Arquivo Servo;
	int i,j,validar;
	fseek(arq,0,0);
	fread(&Servo,sizeof(Arquivo),1,arq);
	if(Servo.key==1){
		do{
			printf("\nJa existe um jogo salvo deseja sobrescrevelo \n1_Sim\n2_Nao\nOpcao: ");
			scanf("%d",&validar);
			switch(validar){
			case 1:fseek(arq,0,0);
				break;
			case 2:fclose(arq);
				return;
				break;
			default:printf("\nOpcao invalida!!");
				break;
			}
		}while(validar!=1);
	                }
	Servo.trade=trade;
	Servo.modo=modo;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			Servo.Jogo[i][j]=Jogo[i][j];
		                }
	                }
	Servo.key=key;
	fwrite(&Servo,sizeof(Arquivo),1,arq);
	fclose(arq);
                                                                      }


void Desafio_Maquina(FILE *arq,int trade,char preenchimento){  //Acho que aqui deveria ao inves de chamar um modo de jogo deveria chamar a inteligencia a qual  jogar
	int modo;
	do{
printf("\n1_facil\n2_medio\n3_dificil\nOpcao: ");
scanf("%d",&modo);
switch(modo){
case 1:Modo_Facil(arq,&trade,preenchimento);
	return;
	break;
case 2:Modo_Medio(arq,&trade,preenchimento);
	return;
	break;
case 3:Modo_Dificil(arq,&trade,preenchimento);
	return;
	break;
default: break;
            }
	  }while(1);//escolha do modo de jogo
                                         }


void Modo_Facil(FILE *arq,int *trade,char preenchimeto){

                                                       }
