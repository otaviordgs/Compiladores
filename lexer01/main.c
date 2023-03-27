#include <stdio.h>
#include <string.h>

enum Token { SOMA, SUBTRACAO, INDERTEMINADO, ESPACO, MULTIPLICACAO, DIVISAO};

void tokenizar(char *palavra) {
  // printf("%s",palavra);
  int cont = 0;
	int tam_palavra = strlen(palavra);
  enum Token tokens[sizeof(palavra)];

  // printf("O tamanho da palavra recebida é: %d\n", tam_palavra);

  for (int i = 0; i < tam_palavra; i++) {
    char temp = palavra[i];

    if (temp == '+') {
      tokens[cont] = SOMA;
      cont++;
    } else if (temp == '-') {
      tokens[cont] = SUBTRACAO;
      cont++;
    } else if (temp == ' '){
			tokens[cont] = ESPACO;
			cont++;	
		} else if (temp == '*'){
			tokens[cont] = MULTIPLICACAO;
			cont++;	
		} else if (temp == '/'){
			tokens[cont] = DIVISAO;
			cont++;
		}
    else {
      tokens[cont] = INDERTEMINADO;
      cont++;
    }
  }

  for (int i = 0; i < tam_palavra; i++) {
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
