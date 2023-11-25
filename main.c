#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mips
{
    char opcode[10];
    int rs;
    int rt;
    int rd;
    int shift;
    int funct;
    int offset;
};

int registradores[32];
int pc = 0;

void imprimirEstado() // aqui coloca oq vai dar print antes de pedir cada instrução
{
    printf("PC: %d\n", pc);
}

void processarInstrucao(struct Mips *instrucao)
{

    printf("Opcode: %s\n", instrucao->opcode);
    printf("rs: %d\n", instrucao->rs);
    printf("rt: %d\n", instrucao->rt);
    printf("rd: %d\n", instrucao->rd);
    printf("shamt: %d\n", instrucao->shift);
    printf("funct: %d\n", instrucao->funct);
    printf("offset: %d\n", instrucao->offset);

    if (strcmp(instrucao->opcode, "add") == 0)
    {
        registradores[instrucao->rd] = registradores[instrucao->rs] + registradores[instrucao->rt];
    }
    else if (strcmp(instrucao->opcode, "sub") == 0)
    {
        registradores[instrucao->rd] = registradores[instrucao->rs] - registradores[instrucao->rt];
    }
    
    pc += 4;
}

int main()
{
    struct Mips instrucao;

    char escolha;

    do
    {
        imprimirEstado();

        printf("Digite a instrucao MIPS (por exemplo, ADD $s1, $s2, $s3): ");
        scanf("%s $%d , $%d , $%d", instrucao.opcode, &instrucao.rs, &instrucao.rt, &instrucao.rd);

        processarInstrucao(&instrucao);

        while (getchar() != '\n')
            ;

        printf("Deseja adicionar mais instrucoes? (s para sim, qualquer outra tecla para sair): ");
        scanf(" %c", &escolha);

    } while (escolha == 's' || escolha == 'S');

    imprimirEstado();

    return 0;
}
