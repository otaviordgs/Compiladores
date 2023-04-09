#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum { 
  SOMA,
  SUBTRACAO,
  INDERTEMINADO,
  ESPACO,
  MULTIPLICACAO,
  DIVISAO,
  POTENCIA,
  NUMERO,
  RESOLVIDO
} Token;

typedef struct
{
	/* data */
	char caracter[10];
	Token tipo_char;
} Valor;


bool isNumber(char character){
    int number = (int)character;
    if(number >= 48 && number <= 57)
        return true;
    
    return false;
} 

bool isPoint(char character){
    int number = (int)character;
    if(number == 46)
        return true;
    
    return false;
}



void tokenizar(char *palavra) {
  // printf("%s",palavra);
  int cont = 0;
  int tam_palavra = strlen(palavra);
  Valor tokens[tam_palavra];
  
  // enum Token tokens[sizeof(palavra)];
  int skipFor = 0;

  // printf("O tamanho da palavra recebida é: %d\n", tam_palavra);

  for (int i = 0; i < tam_palavra; i++) {
    char temp = palavra[i];
    char nextChar = palavra[i + 1];
  

    if(skipFor == 0){
      tokens[cont].caracter[0] = temp;
      if (temp == '+') {
      tokens[cont].tipo_char = SOMA;
      cont++;
      } else if (temp == '-') {
        tokens[cont].tipo_char = SUBTRACAO;
        cont++;
      } else if (temp == ' '){
        tokens[cont].tipo_char = ESPACO;
        cont++;	
      } else if (temp == '/'){
        tokens[cont].tipo_char = DIVISAO;
        cont++;
      } else if (temp == '*'){
        // printf("Opaa 1\n");
        if(nextChar == '*'){
          tokens[cont].tipo_char = POTENCIA;
          skipFor ++;
          // printf("Opaa 2 e cont: %d\n", cont);
        } else {
          tokens[cont].tipo_char = MULTIPLICACAO;
          // printf("Opaa 3 e cont: %d\n", cont);
        }
        cont ++;
      } else if(isNumber(temp)){
          tokens[cont].tipo_char = NUMERO;
          int posicao_numero = 1;
          while(isNumber(nextChar) || isPoint(nextChar)){
            tokens[cont].caracter[posicao_numero] = nextChar;
            posicao_numero++;
            nextChar = palavra[posicao_numero];
          }
          skipFor = posicao_numero - 1;
          cont++;
      }
      else {
        tokens[cont].tipo_char = INDERTEMINADO;
        cont++;
      }
    } else{
      skipFor --;
      // printf("Skipped on char %c and cont %d\n", temp, cont);
    }

    
  }

  // printf("O primeiro numero é %s\n", tokens[0].caracter);
  double resultado;
  
  // nao sei pq mas a ultima posicão sempre é um sina de mais agr
  // isso aconteceu depois da implemenacao do skipfor
  for (int i = 0; i < tam_palavra; i++) {

    switch (tokens[i].tipo_char) {
    case INDERTEMINADO:
      printf("Inderteminado\n");
      break;

    case SOMA:
      // printf("Soma\n");
      resultado = atof(tokens[i-1].caracter) + atof(tokens[i+1].caracter);
      printf("O resultado é: %f\n", resultado);
      break;

    case SUBTRACAO:
      // printf("Subtração\n");
      resultado = atof(tokens[i-1].caracter) - atof(tokens[i+1].caracter);
      printf("O resultado é: %f\n", resultado);
      break;

		case ESPACO:
      printf("Espaço\n");
      break;

		case MULTIPLICACAO:
			// printf("Multiplicação\n");
      resultado = atof(tokens[i-1].caracter) * atof(tokens[i+1].caracter);
      printf("O resultado é: %f\n", resultado);
			break;

		case DIVISAO:
			// printf("Divisão\n");
      resultado = atof(tokens[i-1].caracter) / atof(tokens[i+1].caracter);
      printf("O resultado é: %f\n", resultado);
			break;
    
    case POTENCIA:
			// printf("Potência\n");
      resultado =  (int) pow(atoi(tokens[i-1].caracter), atoi(tokens[i+1].caracter));
      printf("O resultado é: %f\n", resultado);
			break;
    
     case NUMERO:
			// printf("Número\n");
			break;

    default:
      break;
    }
  }
}

int main( int argc, char *argv[ ]) {
  // printf("Hello World\n");
	FILE *arquivo;
 	char linha[100];
	int i;	

	arquivo = fopen(argv[1], "r");
 	if (arquivo == NULL)  // Se houve erro na abertura
  {
     printf("Erro ao abrir arquivo\n");
     return -1;
  }
  // arquivo = fopen("../teste.txt", "r");

	while(fgets(linha, 100, arquivo)) {
        tokenizar(linha);
	}

  fclose(arquivo);
	
  // tokenizar("-+  !/*");
  return 0;
}

