#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum Token { SOMA, SUBTRACAO, INDERTEMINADO, ESPACO, MULTIPLICACAO, DIVISAO, POTENCIA, NUMERO};

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
  enum Token tokens[sizeof(palavra)];
  bool skipFor = false;

  // printf("O tamanho da palavra recebida é: %d\n", tam_palavra);

  for (int i = 0; i < tam_palavra; i++) {
    char temp = palavra[i];
    char nextChar = palavra[i + 1];

    if(skipFor == false){
      if (temp == '+') {
      tokens[cont] = SOMA;
      cont++;
      } else if (temp == '-') {
        tokens[cont] = SUBTRACAO;
        cont++;
      } else if (temp == ' '){
        tokens[cont] = ESPACO;
        cont++;	
      } else if (temp == '/'){
        tokens[cont] = DIVISAO;
        cont++;
      } else if (temp == '*'){
        // printf("Opaa 1\n");
        if(nextChar == '*'){
          tokens[cont] = POTENCIA;
          skipFor = true;
          // printf("Opaa 2 e cont: %d\n", cont);
        } else {
          tokens[cont] = MULTIPLICACAO;
          // printf("Opaa 3 e cont: %d\n", cont);
        }
        cont ++;
      } else if(isNumber(temp)){
          tokens[cont] = NUMERO;
      }
      else {
        tokens[cont] = INDERTEMINADO;
        cont++;
      }
    } else{
      skipFor = false;
      // printf("Skipped on char %c and cont %d\n", temp, cont);
    }

    
  }
  
  // nao sei pq mas a ultima posicão sempre é um sina de mais agr
  // isso aconteceu depois da implemenacao do skipfor
  for (int i = 0; i < tam_palavra - 1; i++) {
    switch (tokens[i]) {
    case INDERTEMINADO:
      printf("Inderteminado\n");
      break;

    case SOMA:
      printf("Soma\n");
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

	arquivo = fopen(argv[1], "r");
 	if (arquivo == NULL)  // Se houve erro na abertura
  {
     printf("Erro ao abrir arquivo\n");
     return -1;
  }

	while(fgets(linha, 100, arquivo)) {
        tokenizar(linha);
	}

  fclose(arquivo);
	
  // tokenizar("-+  !/*");
  return 0;
}

