#include <stdio.h>
#include <string.h>
#define MAX_PARTICIPANTES 1000
#define MAX_MENSAGENS 10000
#define MAX_CARACTERES 140


typedef struct {
	int utilizador;
	char texto[MAX_CARACTERES+1];
}Mensagem;

Mensagem mensagens[MAX_MENSAGENS];
int n_mensagens=0; //numero total de mensagens enviadas
int aux[MAX_MENSAGENS]; //vetor auxiliar usado na ordenacao das mensagens

void LeLinha(char s[], long int a);
int extraiParticipante(char s[]);
void extraiTexto(char s[],int a);
int adicionaMensagem(char s[]);
void imprimeTodas();
int extraiUser(char s[]);
void imprimeMensagensUser(char s[]);
void maisLonga();
void maisAtivo();
void contaPalavra(char s[]);
void merge(int a[], int l, int r, int m);
void mergeSort(int a[],int l,int r);
void ordenaMensagens();

int main(){
	char comando[MAX_CARACTERES+8]; /*No maximo cada cada comando vai ter 147 caracteres*/
	
	while(comando[0]!='X'){
		LeLinha(comando,MAX_CARACTERES+8);
		switch(comando[0]){
			case 'A':
				n_mensagens=adicionaMensagem(comando);
				break;
			case 'L':
				imprimeTodas();
				break;
			case 'U':
				imprimeMensagensUser(comando);
				break;
			case 'O':
				maisLonga();
				break;
			case 'T':
				maisAtivo();
				break;
			case 'C':
				contaPalavra(comando);
				break;
			case 'S':
				ordenaMensagens();
				break;
			case 'X':
				printf("%d\n",n_mensagens);
				break;
			default:
				break;
				
		}
	}
	return 0;
}

void LeLinha(char s[], long int a){
	char c;
	int i;
	
	c=getchar();
	for(i=0;i<a-1 && c!=EOF && c!='\n';i++) {
		s[i]=c;
		c=getchar();
	}
	s[i]='\0';
}


int extraiParticipante(char s[]){
	int i=2;
	mensagens[n_mensagens].utilizador=0;
	
	while(i<=4){ //o numero comeca na posicao 2
		if(s[i]<'0'||s[i]>'9')
			break;
		else
			mensagens[n_mensagens].utilizador=mensagens[n_mensagens].utilizador*10+((int)s[i]-48);
		i++;
	}
	return i+1; //devolve a posicao do vetor onde comeca a mensagem propriamente dita
}

void extraiTexto(char s[],int a){
	int i,j;
	
	for(i=a,j=0;i<MAX_CARACTERES+8;i++,j++)
		mensagens[n_mensagens].texto[j]=s[i];
}
int adicionaMensagem(char s[]){
	int a;
	a=extraiParticipante(s);
	
	extraiTexto(s,a);
	n_mensagens++;
	
	return n_mensagens;
	
}

void imprimeTodas(){
	int i=0;
	
	printf("*TOTAL MESSAGES:%d\n",n_mensagens);
	while(i<n_mensagens){
		printf("%d:%s\n",mensagens[i].utilizador,mensagens[i].texto);
		i++;
		
	}
}

int extraiUser(char s[]){
	int i=2,user=0;
	
	while(i<=4){
		if(s[i]<'0'||s[i]>'9')
			break;
		else
			user=user*10+((int)s[i]-48);
		i++;
	}
	return user;
}

void imprimeMensagensUser(char s[]){
	int i,user;
	
	user=extraiUser(s);
	
	printf("*MESSAGES FROM USER:%d\n",user);
	
	for(i=0;i<n_mensagens;i++)
		if(mensagens[i].utilizador==user){
			printf("%s\n",mensagens[i].texto);
		}
}

void maisLonga(){
	int i,j,maior=0;
	long int tamanho;
	
	for(i=0;i<n_mensagens;i++)
		if(strlen(mensagens[i].texto)>strlen(mensagens[maior].texto))
			maior=i; //no caso de a frase maior ocorrer mais que 1 vez a variavel guarda a posicao da primeira ocorrencia
	
	tamanho=strlen(mensagens[maior].texto);
	
	for(j=0;j<n_mensagens;j++){
		if(strlen(mensagens[j].texto)==tamanho)
			printf("*LONGEST SENTENCE:%d:%s\n",mensagens[j].utilizador,mensagens[j].texto); //imprime todas as ocorrencias da frase maior pela ordem que foram introduzidas no sistema
	}
}

void maisAtivo(){
	int i,maisatv=0;
	int mensagensporuser[MAX_PARTICIPANTES]; //vetor  que contem o numero de mensagens de cada user
	
	for(i=0;i<MAX_PARTICIPANTES;i++)
		mensagensporuser[i]=0; //inicializa o vetor a 0s
	
	for(i=0;i<n_mensagens;i++)
		mensagensporuser[mensagens[i].utilizador]++;//verifica o numero de ocorrencias de cada user na totalidade das mensagens

	
	for(i=1;i<MAX_PARTICIPANTES;i++)
		if(mensagensporuser[i]>mensagensporuser[maisatv])
			maisatv=i; //no caso de haver mais que 1 user mais ativo a variavel guarda a posicao da primeira ocorrencia
	
	for(i=0;i<MAX_PARTICIPANTES;i++)
		if(mensagensporuser[i]==mensagensporuser[maisatv])
			printf("*MOST ACTIVE USER:%d:%d\n",i,mensagensporuser[i]);
}

void contaPalavra(char s[]){
	int i=2,j=0,k=0,contador=0;
	char palavra[MAX_CARACTERES],aux[MAX_CARACTERES];
	
	while(s[i]!='\0'){
		palavra[j++]=s[i++];//extrai a palavra do comando para um novo vetor
	}
	palavra[j]='\0';
	
	for(i=0;i<n_mensagens;i++){
		long int tamanho_frase=strlen(mensagens[i].texto);
		for(j=0;j<=tamanho_frase;j++){
			char caracter=mensagens[i].texto[j];
			if(caracter!= ';' && caracter != '.' && caracter != ',' && caracter != ' ' && caracter != '\t' && caracter != '\n' && caracter != '\0'){
				aux[k]=caracter;//copia cada palavra das mensagens para um vetor auxiliar
				k++;
			}
			else{
				aux[k]='\0';
				if(strcmp(palavra,aux)==0)//verifica se a palavra que se procura e a palavra no vetor auxiliar sao iguais
					contador++;
				k=0;
			}
		}
	}
	printf("*WORD %s:%d\n",palavra,contador);
}

void merge(int a[], int l, int m, int r)
{
	int i, j, k;
	for (i = m+1; i > l; i--)
		aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = a[j+1];
	for (k = l; k <= r; k++){
		int comp=strcmp(mensagens[aux[j]].texto,mensagens[aux[i]].texto);
		if (comp<0)
			a[k] = aux[j--];
		else if(comp==0 && mensagens[aux[j]].utilizador<mensagens[aux[i]].utilizador)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	}
}

void mergeSort(int a[], int l, int r)
{
	int m = (r+l)/2;
	if (r <= l) return;
	mergeSort(a, l, m);
	mergeSort(a, m+1, r);
	merge(a, l, m, r);
}

void ordenaMensagens(){
	int i;
	int indices[n_mensagens];
	
	for(i=0;i<n_mensagens;i++)
		indices[i]=i;//vetor auxiliar que contem os indices de cada mensagem
	
	mergeSort(indices,0,n_mensagens-1);
	
	printf("*SORTED MESSAGES:%d\n",n_mensagens);
	for(i=0;i<n_mensagens;i++)
		printf("%d:%s\n",mensagens[indices[i]].utilizador,mensagens[indices[i]].texto);
}
