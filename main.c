#include <stdio.h>
#include <stdint.h>

#define PC 31

typedef struct Cpu
{
    int registradores[32];
    int memory[5000];
} CpuStruc;

void increment_PC(CpuStruc *cpu)
{
    cpu->registradores[PC] += 4;
}

void RecebeRegs(int *rd, int *rs, int *rt)
{
    printf("Rd: ");
    scanf("%d", rd);
    printf("Rs: ");
    scanf("%d", rs);
    printf("Rt: ");
    scanf("%d", rt);
}

void GuardarNaMem(int *reg, int *ram)
{
    printf("Registrador: ");
    scanf("%d", reg);
    printf("Ram: ");
    scanf("%d", ram);
}

void Jump(int *data)
{
    printf("Memoria: ");
    scanf("%d", data);
}

void PrintRegistradores(CpuStruc *cpu, int r)
{
    printf("\nR%d: %d\n", r, cpu->registradores[r]);
}

void printMem(CpuStruc *cpu, int ram, int offset)
{
    printf("RAM(%d --> %d): ", ram, ram + offset - 1);

    for (int i = 0; i < offset; i++)
    {
        printf("%d ", cpu->memory[ram + i]);
    }

    printf("\n");
}

void add(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] + cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void sub(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] - cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void sw(CpuStruc *cpu)
{
    int rs, ram;
    GuardarNaMem(&rs, &ram);

    cpu->memory[ram] = cpu->registradores[rs];

    printMem(cpu, ram, 1);
}

void lw(CpuStruc *cpu)
{
    int rd, ram;
    GuardarNaMem(&rd, &ram);

    cpu->registradores[rd] = (int32_t)cpu->memory[ram];

    printMem(cpu, ram, 1);
    PrintRegistradores(cpu, rd);
}

void li(CpuStruc *cpu)
{
    int rd, i;

    printf("Rd: ");
    scanf("%d", &rd);
    printf("i: ");
    scanf("%d", &i);

    cpu->registradores[rd] = i;
    PrintRegistradores(cpu, rd);
}

void j(CpuStruc *cpu)
{
    int address;
    Jump(&address);

    cpu->registradores[PC] = address;
}

void addi(CpuStruc *cpu)
{
    int rt, rs, immediate;
    printf("Rt: ");
    scanf("%d", &rt);
    printf("Rs: ");
    scanf("%d", &rs);
    printf("Immediate: ");
    scanf("%d", &immediate);

    cpu->registradores[rt] = cpu->registradores[rs] + immediate;

    PrintRegistradores(cpu, rt);
}

void move(CpuStruc *cpu)
{
    int rd, rs;
    RecebeRegs(&rd, &rs, NULL);

    cpu->registradores[rd] = cpu->registradores[rs];

    PrintRegistradores(cpu, rd);
}

void addu(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = (uint32_t)cpu->registradores[rs] + (uint32_t)cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void mul(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] * cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void and_instr(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] & cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void andi(CpuStruc *cpu)
{
    int rt, rs, immediate;
    printf("Rt: ");
    scanf("%d", &rt);
    printf("Rs: ");
    scanf("%d", &rs);
    printf("Immediate: ");
    scanf("%d", &immediate);

    cpu->registradores[rt] = cpu->registradores[rs] & immediate;

    PrintRegistradores(cpu, rt);
}

void nor(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = ~(cpu->registradores[rs] | cpu->registradores[rt]);

    PrintRegistradores(cpu, rd);
}

void or_instr(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] | cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void xor_instr(CpuStruc *cpu)
{
    int rd, rs, rt;
    RecebeRegs(&rd, &rs, &rt);

    cpu->registradores[rd] = cpu->registradores[rs] ^ cpu->registradores[rt];

    PrintRegistradores(cpu, rd);
}

void xori(CpuStruc *cpu)
{
    int rt, rs, immediate;
    printf("Rt: ");
    scanf("%d", &rt);
    printf("Rs: ");
    scanf("%d", &rs);
    printf("Immediate: ");
    scanf("%d", &immediate);

    cpu->registradores[rt] = cpu->registradores[rs] ^ immediate;

    PrintRegistradores(cpu, rt);
}

void beq(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] == cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

void blt(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] < cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

void ble(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] <= cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

void bgt(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] > cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

void bge(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] >= cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

void bne(CpuStruc *cpu)
{
    int rs, rt, offset;
    RecebeRegs(NULL, &rs, &rt);

    printf("Offset: ");
    scanf("%d", &offset);

    if (cpu->registradores[rs] != cpu->registradores[rt])
    {
        cpu->registradores[PC] += offset;
    }
}

int main()
{
    CpuStruc cpu;

    for (int i = 0; i < 32; i++)
    {
        cpu.registradores[i] = 0;
    }

    char op[6];

    for (;;)
    {
        printf("\n\nDigite uma operacao:\n> ");
        scanf("%5s", op);

        printf("PC: %d\n", cpu.registradores[PC]);

        if (strcmp(op, "add") == 0)
        {
            add(&cpu);
        }
        else if (strcmp(op, "sub") == 0)
        {
            sub(&cpu);
        }
        else if (strcmp(op, "sw") == 0)
        {
            sw(&cpu);
        }
        else if (strcmp(op, "lw") == 0)
        {
            lw(&cpu);
        }
        else if (strcmp(op, "li") == 0)
        {
            li(&cpu);
        }
        else if (strcmp(op, "j") == 0)
        {
            j(&cpu);
        }
        else if (strcmp(op, "addi") == 0)
        {
            addi(&cpu);
        }
        else if (strcmp(op, "move") == 0)
        {
            move(&cpu);
        }
        else if (strcmp(op, "addu") == 0)
        {
            addu(&cpu);
        }
        else if (strcmp(op, "mul") == 0)
        {
            mul(&cpu);
        }
        else if (strcmp(op, "and") == 0)
        {
            and_instr(&cpu);
        }
        else if (strcmp(op, "andi") == 0)
        {
            andi(&cpu);
        }
        else if (strcmp(op, "nor") == 0)
        {
            nor(&cpu);
        }
        else if (strcmp(op, "or") == 0)
        {
            or_instr(&cpu);
        }
        else if (strcmp(op, "xor") == 0)
        {
            xor_instr(&cpu);
        }
        else if (strcmp(op, "xori") == 0)
        {
            xori(&cpu);
        }
        else if (strcmp(op, "beq") == 0)
        {
            beq(&cpu);
        }
        else if (strcmp(op, "blt") == 0)
        {
            blt(&cpu);
        }
        else if (strcmp(op, "ble") == 0)
        {
            ble(&cpu);
        }
        else if (strcmp(op, "bgt") == 0)
        {
            bgt(&cpu);
        }
        else if (strcmp(op, "bge") == 0)
        {
            bge(&cpu);
        }
        else if (strcmp(op, "bne") == 0)
        {
            bne(&cpu);
        }

        increment_PC(&cpu);
        printf("PC: %d\n", cpu.registradores[PC]);
    }

    return 0;
}
