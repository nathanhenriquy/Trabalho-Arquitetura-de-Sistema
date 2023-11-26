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
int pc = 0;

void imprimirEstado()
{
    printf("PC: %d\n", pc);
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
        registradores[r->rt] = registradores[r->rs] + i->endereco;
    }
    else if (strcmp(r->opcode, "sw") == 0)
    {
        registradores[registradores[r->rs] + i->offset] = registradores[r->rt];
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
    struct MipsR r;
    struct MipsI i;
    struct MipsJ j;

    int cont;
    char escolha;
    char instrucao[100];

    for (cont = 0; cont < 32; cont++)
    {
        registradores[cont] = 0;
    }

    do
    {
        imprimirEstado();

        printf("Digite a instrucao MIPS (por exemplo, ADD $s1, $s2, $s3): ");
        fgets(instrucao, sizeof(instrucao), stdin);

        if (sscanf(instrucao, "%s $s%d, $s%d, $s%d", r.opcode, &r.rs, &r.rt, &r.rd) == 4)
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
            printf("Erro ao ler a instrucao. Certifique-se de que a entrada está correta.\n");
        }

        while (getchar() != '\n');

        printf("Deseja adicionar mais instrucoes? (s para sim, qualquer outra tecla para sair): ");
        scanf(" %c", &escolha);

    } while (escolha == 's' || escolha == 'S');

    imprimirEstado();

    return 0;
}
