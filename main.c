#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// opcode e funct de cada instrução:
#define ADDI_OPCODE 8
#define ANDI_OPCODE 12
#define ORI_OPCODE 13
#define XORI_OPCODE 14
#define LW_OPCODE 35
#define SW_OPCODE 43
#define ADD_FUNCT 32
#define SUB_FUNCT 34
#define AND_FUNCT 36
#define OR_FUNCT 37
#define XOR_FUNCT 38

struct mips 
{
    int opcode;
    int rd;
    int rs;
    int rt;
    int shamt;
    int funct;
    int im;
    char endereco[26]; //26 bits de endereço para ser usado na instrução tipo J
};

/*struct MipsR
{
    char opcode[10];
    int rs;
    int rt;
    int rd;
    int shift;
    int funct;
    int offset;
};

struct MipsI
{
    char opcode[10];
    int rd;
    int rs;
    int endereco;
    int offset;
};

struct MipsJ
{
    char opcode[10];
    int endereco;
}; */

int returnOpcode(char *input) 
{
    if (strcmp(input, "ADDI") == 0 || strcmp(input, "addi") == 0) 
        return ADDI_OPCODE; 
    else if (strcmp(input, "ANDI") == 0 || strcmp(input, "andi") == 0) 
        return ANDI_OPCODE; 
    else if (strcmp(input, "ORI") == 0 || strcmp(input, "ori") == 0) 
        return ORI_OPCODE; 
    else if (strcmp(input, "XORI") == 0 || strcmp(input, "xori") == 0) 
        return XORI_OPCODE; 
    else if (strcmp(input, "LW") == 0 || strcmp(input, "lw") == 0) 
        return LW_OPCODE; 
    else if (strcmp(input, "SW") == 0 || strcmp(input, "sw") == 0) 
        return SW_OPCODE; 
    else if (strcmp(input, "ADD") == 0 || strcmp(input, "add") == 0) 
        return ADD_FUNCT;   
    else if (strcmp(input, "SUB") == 0 || strcmp(input, "sub") == 0) 
        return SUB_FUNCT;   
    else if (strcmp(input, "AND") == 0 || strcmp(input, "and") == 0) 
        return AND_FUNCT;  
    else if (strcmp(input, "OR") == 0 || strcmp(input, "or") == 0) 
        return OR_FUNCT;   
    else if (strcmp(input, "XOR") == 0 || strcmp(input, "xor") == 0) 
        return XOR_FUNCT;   
    else if(strcmp(input, "J") == 0 || strcmp(input, "j") == 0) 
        return 2;   
    else 
    {
        printf("Opcode invalido:\n");
        return -1; 
    }
}

int decBin(int bin) 
{
    if (bin == 0)
        return 0; 
    else 
        return (bin % 2) + 10 * decBin(bin / 2);
}

void preencheInstrucao
(int opcode, int rd, int rs, int rt, int shamt, int funct, int im, int endereco, struct mips *mips)
{
    mips->opcode = opcode;
    mips->rs = rs;
    mips->rt = rt;
    mips->rd = rd;
    mips->shamt = shamt;
    mips->funct = funct;
    mips->im = im;
}

void preencheInstrucaoBin
(struct mips *instrucao_binario, struct mips *instrucao)
{
    instrucao_binario->opcode = decBin(instrucao->opcode);
    instrucao_binario->rs = decBin(instrucao->rs);
    instrucao_binario->rt = decBin(instrucao->rt);
    instrucao_binario->rd = decBin(instrucao->rd);
    instrucao_binario->shamt = decBin(instrucao->shamt);
    instrucao_binario->funct = decBin(instrucao->funct);
    instrucao_binario->im = decBin(instrucao->im);
}

int ula(int opcode, int operando1, int operando2){
    switch (opcode) {
        case 8:
            return operando1 + operando2;
        case 32:
        case 35:
        case 43:
            return operando1 + operando2;
        case 34: 
            return operando1 - operando2;
        case 2:
            return operando1 * operando2;
        case 3:
            return operando1 / operando2; 
        case 13:
        case 37:
            return operando1 | operando2; 
        case 12:
        case 36:
            return operando1 & operando2;
        case 14:
        case 38:
            return operando1 ^ operando2;
        default: 
            printf("Operacao invalida\n");
            return -1;
    }
    
}

int registrador[32];

void processarInstrucao(struct mips *m)
{
    

    printf("Opcode: %s\n", m->opcode);
    printf("rs: %d\n", m->rs);
    printf("rt: %d\n", m->rt);
    printf("rd: %d\n", m->rd);
    printf("shamt: %d\n", m->shamt);
    printf("funct: %d\n", m->funct);

    if (strcmp(m->opcode, "add") == 0)
    {
        registrador[m->rd] = registrador[m->rs] + registrador[m->rt];
    }
    else if (strcmp(m->opcode, "sub") == 0)
    {
        registrador[m->rd] = registrador[m->rs] - registrador[m->rt];
    }
    else if (strcmp(m->opcode, "lw") == 0)
    {
        registrador[m->rt] = registrador[m->rs] + m->endereco;
    }
    else if (strcmp(m->opcode, "sw") == 0)
    {
        registrador[m->rt] = registrador[m->rs] + m->offset;
    }
    else if (strcmp(m->opcode, "j") == 0)
    {
        pc = m->endereco;
    }

    pc += 4;
}

int pc = 0;

void imprimirEstado() // aqui coloca oq vai dar print antes de pedir cada instrução
{
    printf("PC: %d\n", pc);
}

int main()
{
    int i;
    char escolha;
    char input[100];
    char instrucao_mips[100]; 

    struct mips *m;

    // m->opcode = returnOpcode(input);

    for (i = 0; i < strlen(registrador); i++)
    {
        registrador[i] = 0;
    }

    
    do
    {
        imprimirEstado();

        printf("Digite a instrucao MIPS (por exemplo, ADD $s1, $s2, $s3): ");
        fgets(input, sizeof(input), stdin);

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') 
        {
            input[len - 1] = '\0';
        }

        char input_temp[100];
        strcpy(input_temp, input);
        char *token = strtok(input_temp, " \t\n");
        if (token != NULL) {
        sscanf(token, "%s", instrucao_mips);


        if (sscanf(input, "%s $s%d, $s%d, $s%d", m->opcode, &m->rs, &m->rt, &m->rd) == 4)
        {
            processarInstrucao(&m);
        }
        else if (sscanf(input, "%s $s%d, %d", m->opcode, &m->rd, &m->endereco) == 3)
        {
            processarInstrucao(&m);
        }
        else if (sscanf(input, "%s %d", m->opcode, &m->endereco) == 2)
        {
            processarInstrucao(&m);
        }
        else
        {
            printf("Erro ao ler a instrucao. Certifique-se de que a entrada está correta.\n");
        }

        while (getchar() != '\n');

        printf("Deseja adicionar mais instrucoes? (s para sim, qualquer outra tecla para sair): ");
        scanf(" %c", &escolha);

    } while (escolha == 's' || escolha == 'S');

    imprimirEstado();

    return 0;
}