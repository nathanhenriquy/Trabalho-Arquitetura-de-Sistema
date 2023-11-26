#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MipsR
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
};

int registradores[32];
int memoria[100];  // Adicionando uma memória para armazenar dados
int pc = 0;

void imprimirEstado()
{
    printf("PC: %d\n", pc);
    for (int i = 0; i < 32; i++)
    {
        printf("$s%d: %d\n", i, registradores[i]);
    }
    printf("Memória:\n");
    for (int i = 0; i < 100; i++)
    {
        printf("Mem[%d]: %d\n", i, memoria[i]);
    }
}

void processarInstrucao(struct MipsR *r, struct MipsI *i, struct MipsJ *j)
{
    printf("Opcode: %s\n", r->opcode);
    printf("rs: %d\n", r->rs);
    printf("rt: %d\n", r->rt);
    printf("rd: %d\n", r->rd);
    printf("shamt: %d\n", r->shift);
    printf("funct: %d\n", r->funct);
    printf("offset: %d\n", r->offset);

    if (strcmp(r->opcode, "add") == 0)
    {
        registradores[r->rd] = registradores[r->rs] + registradores[r->rt];
    }
    else if (strcmp(r->opcode, "sub") == 0)
    {
        registradores[r->rd] = registradores[r->rs] - registradores[r->rt];
    }
    else if (strcmp(r->opcode, "lw") == 0)
    {
        registradores[r->rt] = memoria[r->rs + i->endereco];
    }
    else if (strcmp(r->opcode, "sw") == 0)
    {
        memoria[r->rs + i->offset] = registradores[r->rt];
    }
    else if (strcmp(j->opcode, "j") == 0)
    {
        pc = j->endereco;
        return;
    }

    pc += 4;
}

int main()
{
    int cont;
    char escolha;
    char instrucao[100];

    for (cont = 0; cont < 32; cont++)
    {
        registradores[cont] = 0;
    }

    for (cont = 0; cont < 100; cont++)
    {
        memoria[cont] = 0;
    }

    do
    {
        imprimirEstado();

        printf("Digite a instrução MIPS (por exemplo, ADD $s1, $s2, $s3): ");
        fgets(instrucao, sizeof(instrucao), stdin);
        
        struct MipsR r = {0}; // Inicializa a estrutura com zeros
        struct MipsI i = {0};
        struct MipsJ j = {0};


        if (sscanf(instrucao, "%s $s%d, %d($s%d)", r.opcode, &r.rt, &i.offset, &r.rs) == 4)
        {
            processarInstrucao(&r, &i, &j);
        }
        else if (sscanf(instrucao, "%s $s%d, %d", r.opcode, &i.rd, &i.endereco) == 3)
        {
            processarInstrucao(&r, &i, &j);
        }
        else if (sscanf(instrucao, "%s %d", j.opcode, &j.endereco) == 2)
        {
            processarInstrucao(&r, &i, &j);
        }
        else
        {
            printf("Erro ao ler a instrução. Certifique-se de que a entrada está correta.\n");
        }

        while (getchar() != '\n');

        printf("Deseja adicionar mais instruções? (s para sim, qualquer outra tecla para sair): ");
        scanf(" %c", &escolha);

    } while (escolha == 's' || escolha == 'S');

    imprimirEstado();

    return 0;
}