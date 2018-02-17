#include <stdio.h>

# define READ       10
# define WRITE      11

# define LOAD       20
# define STORE      21

# define ADD        30
# define SUBTRACT   31
# define DIVIDE     32
# define MULTIPLY   33

# define BRANCH     40
# define BRANCHNEG  41
# define BRANCHZERO 42
# define HALT       43


void printMemory(int arr[]){
    printf("\n");
    for(int i = 0 ; i < 100 ; i++){ printf("%d : %d\t\t", i, arr[i]); }
    printf("\n");
    return;
}

void inputProgramFromConsole(int memory[]) {
    int i = 0;
    int opcode;

    printf("Enter Byte Codes:\n");
    scanf("%d", &opcode);

    while(opcode != -99999){
        memory[i] = opcode;
        i++;
        scanf("%d", &opcode);
    }
    return;
}

int getOpcode(int full){ return full / 100; }

int getValue(int full){ return full % 100; }

void execute(int* machineHead, int* accumulator, int memory[]){
    int opcode = getOpcode(memory[*machineHead]);
    int value = getValue(memory[*machineHead]);

    switch(opcode) {
        case READ :
            printf("READ: ");
            scanf("%d", &memory[value]);
            (*machineHead)++;
            break;
        case WRITE :
            printf("WRITE: ");
            printf("%d, \n", memory[value]);
            (*machineHead)++;
            break;
        case LOAD :
            // printf("load: \n");
            *accumulator = memory[value];
            (*machineHead)++;
            break;
        case STORE :
            // printf("store: \n");
            memory[value] = *accumulator;
            (*machineHead)++;
            break;
        case ADD :
            *accumulator = *accumulator + memory[value];
            (*machineHead)++;
            break;
        case SUBTRACT :
            *accumulator = *accumulator - memory[value];
            (*machineHead)++;
            break;
        case DIVIDE :
            *accumulator = memory[value] / *accumulator;
            (*machineHead)++;
            break;
        case MULTIPLY :
            *accumulator = memory[value] * *accumulator;
            (*machineHead)++;
            break;
        case BRANCH :
            *machineHead = value;
            break;
        case BRANCHNEG :
            if(*accumulator < 0){
                *machineHead = value;
            }else{
                (*machineHead)++;
            }
            break;
        case BRANCHZERO :
            if(*accumulator == 0){
                *machineHead = value;
            }else{
                (*machineHead)++;
            }
            break;        // case HALT :
        case HALT :
            *machineHead = 100;
            break;
        default:
            printf("INVALID OPCODE: '%d'", opcode);
            *machineHead = 100;
            break;
    }
    return;
}

void runProgram(int memory[]){
    if(getOpcode(memory[0]) == 34){ return; }
    int machineHead = 0;
    int accumulator = 0;

    while(machineHead < 100){
        execute(&machineHead, &accumulator, memory);
    }

    return;
}


int main(){
    int memory[100] = { 0 };

    inputProgramFromConsole(memory);

    runProgram(memory);

    printMemory(memory);

    return 0;
}


// sample
// 1007
// 2007
// 2108
// 1108
// 4300
// -99999
