#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
//
typedef struct T_Arquivo{
	int trade,modo;
	char Jogo[3][3],nome[25];
                        }Arquivo;
void New_Game();//OK
void Continue_Game();//OK
void Desafio_Maquina(FILE *arq,int trade,int modo,char preenchimento);//OK
void PvP(FILE *arq,int trade,char preenchimento);//OK
void Printar_Jogo(char Jogo[3][3]);//Falta
int Win_Cond(char Jogo[3][3]); //OK
void Salvar_Jogo(int trade,int modo,char Jogo[3][3]);// OK
void Modo_Facil(char Jogo[3][3]);//Falta
void Modo_Medio(char Jogo[3][3]);//Falta
void Modo_Dificil(char Jogo[3][3]);//Falta


int main(){
	char op;
	do{
		system("cls");
		printf("\n\t--JOGO DA VELHA--\n");
		printf("1_Novo Jogo\n2_Continuar\n3_Sair\nOpcao: ");
		fflush(stdin);
		scanf("%c",&op);
		fflush(stdin);

	switch(op){
	case'1':
		New_Game();
		break;
	case'2':
		Continue_Game();
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


void New_Game(){
	int trade,modo;
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
			do{
			printf("\n Escolha o modo \n1-Facil\n2-Medio\n3-Dificil\nOpcao: ");
			scanf("%i",&modo);
			}while(modo!=1&&modo!=2&&modo!=3);
			srand( (unsigned)time(NULL) );
	        trade=rand()%2;
			Desafio_Maquina(NULL,trade,modo,'n');
			return;
			break;
		case'2':
			srand( (unsigned)time(NULL) );
	        trade=rand()%2;

			PvP(NULL,trade,'n');
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
	int tradelocal=trade,l,c,ok=0,i,j;
	char player1[25],player2[25],aux;
	char Jogo[3][3];
	if(preenchimento=='n'){
		for(i=0;i<3;i++){
			for(j=0;i<3;j++){
				Jogo[i][j]=' ';
			                }
		                }
	                      }
	else{
		
		fread(&Servo,sizeof(Arquivo),1,arq);
		
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
	printf("\n\tPartida Amistosa\n"); 
	
	do{
	Printar_Jogo(Jogo);
	do{
	printf("\nInforme a Linha em que Deseja Inserir 'X' ou 'O': ");
	aux=getch();
	if(aux==19){
		l=19;
	           }
	else{
		l=aux-'0';
	    }           //pega o valor sem enter
	switch(l){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	case 19:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
	  }while(l!=0&&l!=1&&l!=2&&l!=19);                      //valida valor recebido
	if(l==19){
		Salvar_Jogo(tradelocal,1,Jogo);                 //Chama o salvar se for apertado ctrl s
		return;                                            //volta para o menu anterior se salvar
	         }
do{
	printf("\nInforme a Coluna em que Deseja Inserir : ");
	aux=getch();
	if(aux==19){
		c=19;
	           }
	else{
		c=aux-'0';
	    } 
	switch(c){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	case 19:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
   }while(c!=0&&c!=1&&c!=2&&c!=19);    //valida coluna
if(c==19){
		Salvar_Jogo(tradelocal,1,Jogo);                 //Chama o salvar se for apertado ctrl s
		return;
	         }                                     //vai para o menu anterior se for salvo
if(Jogo[l][c]==' '){
	ok=1;
	
	if(tradelocal==0){
		Jogo[l][c]='X';
		if(Win_Cond(Jogo)==1){
			printf("\nO Jogador %s Venceu!!",player1);
			return;
		                     }
		else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
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
		else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
					return;
				                          }
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



void Salvar_Jogo(int trade,int modo,char Jogo[3][3]){
	Arquivo Servo;
	FILE *arq;
	char none_sav[25];
	int ok=0,status,i,j;


	
			arq=fopen("Salve","r+b");
	if(arq==NULL){
		arq=fopen("Salve","w+b");
	             }
	fseek(arq,0,0);
	
	do{
		printf("\nInforme o Nome do seu Salve: ");
		fgets(none_sav,25,stdin);
		do{
			status=fread(&Servo,sizeof(arq),1,arq);
			if(strcmp(Servo.nome,none_sav)==0){
				printf("\nNao e possivel salvar o jogo  o Nome ja esta sendo usado!!");
				break;
			                        } // talvez de tempo de fazer um sobreescrever
			else if (status == 0) {
			if  (feof(arq) != 0){
				ok=1;
				break;
			                    }
                                 
			else
            printf("Erro de leitura");
            break;
                                   }
		  }while(1);
	  }while(ok!=0);   //Valida se o salve nao é repetido
	fseek(arq,0,SEEK_END);
	Servo.modo=modo;
	Servo.trade=trade;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			Servo.Jogo[i][j]=Jogo[i][j];
		                }
	                }
	fwrite(&Jogo,sizeof(Arquivo),1,arq);
	fclose(arq);
                                                                      }


void Desafio_Maquina(FILE *arq,int trade,int modo,char preenchimento){  //Acho que aqui deveria ao inves de chamar um modo de jogo deveria chamar a inteligencia a qual  jogar
	
	Arquivo Servo;
	int tradelocal=trade,l,c,ok=0,i,j,modosav;  //modo sav é para salvar
	char aux;
	char Jogo[3][3];
	switch(modo){
	case 1: modosav=2;
		break;
	case 2: modosav=3;
		break;
	case 3: modosav=4;
		break;
	default: break;
	}

	if(preenchimento=='n'){
		for(i=0;i<3;i++){
			for(j=0;i<3;j++){
				Jogo[i][j]=' ';
			                }
		                }
	                      }
	else{
		
		fread(&Servo,sizeof(Arquivo),1,arq);
		
		for(i=0;i<3;i++){
			for(j=0;i<3;j++){
				Jogo[i][j]=Servo.Jogo[i][j];
			                }
		                }
	    }
	if(tradelocal==0){
	printf("\nO Jogador comeca!!\n");
	}
	else{
	printf("\nA Maquina comeca!!\n");
	}
	do{
		printf("\n\tPartida Contra IA\n"); 
		if(tradelocal==0){
			
	
	do{
	Printar_Jogo(Jogo);
	do{
	printf("\nInforme a Linha em que Deseja Inserir 'X' ou 'O': ");
	aux=getch();
	if(aux==19){
		l=19;
	           }
	else{
		l=aux-'0';
	    }           //pega o valor sem enter
	switch(l){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	case 19:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
	  }while(l!=0&&l!=1&&l!=2&&l!=19);                      //valida valor recebido
	if(l==19){
		Salvar_Jogo(tradelocal,modosav,Jogo);                 //Chama o salvar se for apertado ctrl s
		return;                                            //volta para o menu anterior se salvar
	         }
do{
	printf("\nInforme a Coluna em que Deseja Inserir : ");
	aux=getch();
	if(aux==19){
		c=19;
	           }
	else{
		c=aux-'0';
	    } 
	switch(c){
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	case 19:
		break;
	default:
		printf("\nPosicao Invalida!!");
	}
   }while(c!=0&&c!=1&&c!=2&&c!=19);    //valida coluna
if(c==19){
	Salvar_Jogo(tradelocal,modosav,Jogo);                 //Chama o salvar se for apertado ctrl s
		return;
	         }                                     //vai para o menu anterior se for salvo

if(Jogo[l][c]==' '){
	ok=1;
	Jogo[l][c]='X';               //VER SE TA CERTO !!!!!!!!!!!!!!!!!!!!!!
	if(Win_Cond(Jogo)==1){
		system("cls");
		Printar_Jogo(Jogo);
	printf("\nO Jogador Venceu!!\n");
	return;
	                     }
	else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
					return;
				                          }
                   }//posiçao desocupada
else{
	printf("\n Esta posicao ja esta ocupada!!\n");
    }
	}while(ok!=1);//valida jogada
		}//vez do jogador
		else{
			switch(modo){
			case 1:
				Modo_Facil(Jogo);
				system("cls");
				Printar_Jogo(Jogo);
				if(Win_Cond(Jogo)==1){
					printf("\nA Maquina venceu!!\n");
					return;
				                     }
				else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
					return;
				                          }
				break;
			case 2:
				Modo_Medio(Jogo);
				system("cls");
				Printar_Jogo(Jogo);
				if(Win_Cond(Jogo)==1){
					printf("\nA Maquina venceu!!\n");
					return;
				                     }
				else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
					return;
				                          }
				break;
			case 3:
				Modo_Dificil(Jogo);
				system("cls");
				Printar_Jogo(Jogo);
				if(Win_Cond(Jogo)==1){
					printf("\nA Maquina venceu!!\n");
					return;
				                     }
				else if(Win_Cond(Jogo)==2){
					printf("\nEmpate!!\n");
					return;
				                          }
				break;
			default: break;
			            }   //Escolhe a Inteligencia
		    }//Vez da maquina
	}while(1); //intercalaçao do jogador/maquina

                                         }


void Modo_Facil(char Jogo[3][3]){

                                }

void Modo_Medio(char Jogo[3][3]){
                                }

void Modo_Dificil(char Jogo[3][3]){
                                  }



int Win_Cond(char Jogo[3][3]){
	int cont=0,i,j;
	if(Jogo[0][0]==(Jogo[0][1]+Jogo[0][2])/2)
		return 1;
	else if(Jogo[1][0]==(Jogo[1][1]+Jogo[1][2])/2)
		return 1;
	else if(Jogo[2][0]==(Jogo[2][1]+Jogo[2][2])/2)
		return 1;
	else if(Jogo[0][0]==(Jogo[1][0]+Jogo[2][0])/2)
		return 1;
	else if(Jogo[0][1]==(Jogo[1][1]+Jogo[2][1])/2)
		return 1;
	else if(Jogo[0][2]==(Jogo[1][2]+Jogo[2][2])/2)
		return 1;
	else if(Jogo[0][0]==(Jogo[1][1]+Jogo[2][2])/2)
		return 1;
	else if(Jogo[0][2]==(Jogo[1][1]+Jogo[2][0])/2)
		return 1;
	else{
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(Jogo[i][j]!= ' '){
					cont++;
				                    }
			                }
		                }
		if(cont==9)return 2;
	    }
	return 0;
                             }

void Continue_Game(){
	int ok=0,status;
	char nome[25];
	Arquivo Servo;
	FILE *arq;
	system("cls");
	arq=fopen("Salve","r+b");
	if(arq==NULL){
		arq=fopen("Salve","w+b");
	             }
	fseek(arq,0,0);
	do{
		status = fread (&Servo, sizeof (Arquivo), 1,arq);
if (status == 0) {
	if (feof(arq) != 0){
		ok=1;
		break;
	                   }

else
printf("Erro de leitura");
break;
}
else {
// processamento dos dados lidos
	printf ("\n%s",Servo.nome);

}
	  }while(ok!=1);       //Lista os saves
	ok=0;
	fseek(arq,0,0);
	do{
	printf("\nInforme o nome do jogo que sera carregado: ");
	fgets(nome,25,stdin);
	do{
		status = fread (&Servo, sizeof (Arquivo), 1,arq);
if (status == 0) {
	if (feof(arq) != 0){
		printf("\nJogo nao encontrado!!\n");
		break;
	                   }

else
printf("Erro de leitura");
break;
}
else{
	if(strcmp(Servo.nome,nome)==0){
		fseek(arq,sizeof(Arquivo)*-1,SEEK_SET);   //na teoria isso volta o ponteiro para onde eu preciso pra dps mandolo para os preenchimentos
		switch(Servo.modo){
		case 1:
			PvP(arq,Servo.trade,'c');
			break;
		case 2:
			Desafio_Maquina(arq,Servo.trade,Servo.modo-1,'c');
			break;
		case 3:
			Desafio_Maquina(arq,Servo.trade,Servo.modo-1,'c');
			break;
		case 4:
			Desafio_Maquina(arq,Servo.trade,Servo.modo-1,'c');
			break;
		default:
			break;
		                  }
		ok=1;
		break;
	                              }
    }
	  }while(1); //procura o nome do salve
	  }while(ok!=1);
	fclose(arq);
	return;
                    }
