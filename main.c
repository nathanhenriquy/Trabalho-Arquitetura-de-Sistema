#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int registers[32] = {0};

int memory[1000] = {0};

int pc = 0;

void add(int rd, int rs, int rt) {
    registers[rd] = registers[rs] + registers[rt];
}

void sub(int rd, int rs, int rt) {
    registers[rd] = registers[rs] - registers[rt];
}

void sw(int rt, int base, int offset) {
    memory[base + offset] = registers[rt];
}

void lw(int rt, int base, int offset) {
    registers[rt] = memory[base + offset];
}

void jump(int target) {
    pc = target;
}

int main() {
    char operation[4]; // "ADD\0", "SUB\0", "SW\0", "LW\0", "J\0"
    int rd, rs, rt, base, offset, target;
    int num_instructions;

    printf("Simulador de MIPS\n");

    
    printf("Digite o numero de instrucoes a serem executadas: ");
    scanf("%d", &num_instructions);

    for (int i = 0; i < num_instructions; i++) {
    
        printf("\nDigite a operacao (ADD, SUB, SW, LW, J): ");
        scanf("%3s", operation);

        if (strncmp(operation, "ADD", 3) == 0) {
            scanf("%d %d %d", &rd, &rs, &rt);
            add(rd, rs, rt);
        } else if (strncmp(operation, "SUB", 3) == 0) {
            scanf("%d %d %d", &rd, &rs, &rt);
            sub(rd, rs, rt);
        } else if (strncmp(operation, "SW", 2) == 0) {
            scanf("%d %d %d", &rt, &base, &offset);
            sw(rt, base, offset);
        } else if (strncmp(operation, "LW", 2) == 0) {
            scanf("%d %d %d", &rt, &base, &offset);
            lw(rt, base, offset);
        } else if (strncmp(operation, "J", 1) == 0) {
            scanf("%d", &target);
            jump(target);
        } else {
            printf("Operacao invalida.\n");
            i--; 
            continue;
        }

        printf("\nEstado dos registradores:\n");
        for (int j = 0; j < 32; j++) {
            printf("Reg%d: %d\n", j, registers[j]);
        }

        printf("\nEstado da memoria:\n");
        for (int j = 0; j < 1000; j++) {
            printf("Mem%d: %d\n", j, memory[j]);
        }

        pc += 4;
        printf("Program Counter (PC): %d\n", pc);
    }

    return 0;
}
