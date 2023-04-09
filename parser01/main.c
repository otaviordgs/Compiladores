#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum { SOMA, SUBTRACAO, INDERTEMINADO, ESPACO, MULTIPLICACAO, DIVISAO, POTENCIA, NUMERO} Token;

typedef struct
{
	/* data */
	char caracter;
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
  bool skipFor = false;

  // printf("O tamanho da palavra recebida é: %d\n", tam_palavra);

  for (int i = 0; i < tam_palavra; i++) {
    char temp = palavra[i];
    char nextChar = palavra[i + 1];
    tokens[cont].caracter = temp;
    printf("O index %d e o seu valor %c\n", i,  tokens[cont].caracter);

    if(skipFor == false){
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
          skipFor = true;
          // printf("Opaa 2 e cont: %d\n", cont);
        } else {
          tokens[cont].tipo_char = MULTIPLICACAO;
          // printf("Opaa 3 e cont: %d\n", cont);
        }
        cont ++;
      } else if(isNumber(temp)){
          tokens[cont].tipo_char = NUMERO;
      }
      else {
        tokens[cont].tipo_char = INDERTEMINADO;
        cont++;
      }
    } else{
      skipFor = false;
      // printf("Skipped on char %c and cont %d\n", temp, cont);
    }

    
  }

  printf("O valor do primeiro é %c\n", tokens[0].caracter );
  
  // nao sei pq mas a ultima posicão sempre é um sina de mais agr
  // isso aconteceu depois da implemenacao do skipfor
  for (int i = 0; i < tam_palavra; i++) {
    printf("AHH %c, BB %d\n", tokens[i].caracter, i);

    switch (tokens[i].tipo_char) {
    case INDERTEMINADO:
      printf("Inderteminado\n");
      break;

    case SOMA:
      // printf("Soma\n");
      // printf("O numero anterior é %c e o posterio é %c\n", (tokens[i-1].caracter), (tokens[i+1].caracter));
      // int resultado = atoi(&tokens[i-1].caracter) + atoi(&tokens[i+1].caracter);
      printf("O resultado é: %d\n", resultado);
      break;

    case SUBTRACAO:
      printf("Subtração\n");
      break;

		case ESPACO:
      printf("Espaço\n");
      break;

		case MULTIPLICACAO:
			printf("Multiplicação\n");
			break;

		case DIVISAO:
			printf("Divisão\n");
			break;
    
    case POTENCIA:
			printf("Potência\n");
			break;
    
     case NUMERO:
			printf("Número\n");
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

	// arquivo = fopen(argv[1], "r");
 	// if (arquivo == NULL)  // Se houve erro na abertura
  // {
  //    printf("Erro ao abrir arquivo\n");
  //    return -1;
  }
  arquivo = f

	while(fgets(linha, 100, arquivo)) {
        tokenizar(linha);
	}

  fclose(arquivo);
	
  // tokenizar("-+  !/*");
  return 0;
}

