#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

#define HLT 240
#define STA 16
#define LDA 32
#define ADD 48
#define OR 64
#define AND 80
#define NOT 96
#define JMP 128
#define JN 144
#define JZ 160

uint8_t acc, pos = 0;
int pc, n = 0, z = 0;

void criar_binario(){
    uint8_t buffer[14] =  {42,0,0,32,12,96,48,13,96,16,1,240,10,4};
	FILE *file = fopen("teste.nar", "wb");
	if (file == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
	}

	fwrite(buffer,1, 14, file);
	fclose(file);
	printf("Binario Criado!\n");
}


int main(int argc, char *argv[]){
    
	char *nomeArquivo =  argv[1];
    char *extensao = strrchr(nomeArquivo, '.');
  
	if (strcmp(extensao,".nar") != 0){
		printf("\nO arquivo não está no formato .nar!\n");
		return 1;
	}

	static uint8_t c[255];
	FILE *arquivo;
	arquivo = fopen(nomeArquivo, "r");
	fseek(arquivo, 0, SEEK_SET);
	fread(c, 512, 1, arquivo);

	if(c[0] != 42){
		printf("\nRejeitado! O primeiro byte deve ser 42.");
		return 1;
  	}

	acc = c[1];
	pc = c[2];

	bool continuar = true;

	while(continuar){
		pos = 0;
		if(acc == 0){
			z = 1;
			n = 0;
		}
		else if(acc > 127){
			z = 0;
			n = 1;
		}
		else{
			z = 0;
			n = 0;
		}
		
		//Fim
		if(c[pc] == 240 || pc >= 256){
			continuar = false;
		}
		//STA
		else if(c[pc] == 16){
			pc += 1;
			pos = c[pc];
			
			c[pos] = acc;
		}
		//LDA
		else if(c[pc] == 32){
			pc += 1;
			pos = c[pc];
			
			acc = c[pos];
		}
		//ADD
		else if(c[pc] == 48){
			pc += 1;
			pos = c[pc];
			
			acc += c[pos];
		}
		//OR
		else if(c[pc] == 64){
			pc += 1;
			pos = c[pc];
			
			acc = acc | pos;
		}
		//AND
		else if(c[pc] == 80){
			pc += 1;
			pos = c[pc];
			
			acc = acc & pos;
		}
		//NOT
		else if(c[pc] == 96){
			acc = (acc * -1) - 1;
		}
		//JMP
		else if(c[pc] == 128){
			pc += 1;
			pc = c[pc] - 1;
		}
		//JN
		else if(c[pc] == 144){
			if(n == 1){
				pc += 1;
				pc = c[pc] -1;
			}
		}
		//JZ
		else if(c[pc] == 160){
			if(z == 1){
				pc += 1;
				pc = c[pc] -1;
			}
		}

		pc++;
	}

	printf("Após as modificações.\n");
	printf("Acumulador: %u\nPC: %d\nFlag N: %d\nFlag Z: %d\n",acc,pc,n,z);
	for(int i = 0; i < 256; i++){
		printf("%u ", c[i]);
	}
	printf("\n");

	fclose(arquivo);
    return 0;
}