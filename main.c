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
    int rs;
    int rt;
    int endereco;
    int offset;
};

struct MipsJ
{
    char opcode[10];
    int endereco;
};

int registradores[32];
int pc = 0;

void imprimirEstado() // aqui coloca oq vai dar print antes de pedir cada instrução
{
    printf("PC: %d\n", pc);
}

void processarInstrucao(struct MipsR *r, struct MipsI *i)
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
        registradores[r->rt] = registradores[r->rs] + i->endereco;
    }
    else if (strcmp(r->opcode, "sw") == 0)
    {
        registradores[r->rt] = registradores[r->rs] + i->offset;
    }

    pc += 4;
}

int main()
{
    struct MipsR r;
    struct MipsI i;
    struct MipsJ j;

    char escolha;

    do
    {
        imprimirEstado();

        printf("Digite a instrucao MIPS (por exemplo, ADD $s1, $s2, $s3): ");
        scanf("%s $%d , $%d , $%d", r.opcode, &r.rs, &r.rt, &r.rd);

        if (strcmp(r.opcode, "add") == 0 || strcmp(r.opcode, "sub") == 0)
        {
            scanf("$%d , $%d , $%d", &r.rs, &r.rt, &r.rd);
        }
        else if (strcmp(r.opcode, "lw") == 0)
        {
            scanf("$%d , %d($%d)", &r.rt, &i.endereco, &r.rs);
        }
        else if (strcmp(r.opcode, "sw") == 0)
        {
            scanf("$%d , %d($%d)", &r.rt, &i.offset, &r.rs);
        }

        processarInstrucao(&r, &i);

        while (getchar() != '\n');

        printf("Deseja adicionar mais instrucoes? (s para sim, qualquer outra tecla para sair): ");
        scanf(" %c", &escolha);

    } while (escolha == 's' || escolha == 'S');

    imprimirEstado();

    return 0;
}
