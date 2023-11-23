#include <stdio.h>
#include <stdlib.h>

struct instrucoes{
    
    int opcode;    
    int rs;
    int rt;
    int rd;
    int shamt;
    int funct;
    int offset
} ;

int main()
{
    int pc = 0;
    int registradores[32] = {0}; // Registradores
    int memoria[1024] = {0}; // Memória 


    return 0;
}
