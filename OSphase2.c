#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define VIRTUAL_MEMORY_SIZE 100
#define REAL_MEMORY_SIZE 300
#define PAGE_SIZE 10
#define TOTAL_PAGES (VIRTUAL_MEMORY_SIZE / PAGE_SIZE)

// Interrupt types
#define NO_INTERRUPT 0
#define SI_READ 1   
#define SI_WRITE 2 
#define SI_HALT 3  
#define TI_TIMEOUT 1 
#define PI_INVALID_OPCODE 1 
#define PI_INVALID_PAGE 2    

// Structure for PCB (Process Control Block)
typedef struct {
    int job_id;
    int ttl; 
    int tll; 
    int PTR; 
    int TTC; 
    int LLC; 
} PCB;

// Function prototypes
void init();
void load_program_from_file(FILE*);
void load_program_from_buffer_to_virtual_memory();
void store_instruction_in_real_memory(int VA, char* instruction);
void print_memory();
void address_map(int VA, int *RA);
void execute_program();
void handle_GD(int address);
void handle_PD(int address);
void interrupt_handler(int SI, int TI, int PI);
int generate_random_block();
void update_page_table(int VA, int RA);
void load_register(int address);
void store_register(int address);
void compare_register(int address);
void branch_if_true(int address);

// Memory and registers
char buffer[40]; 
char virtual_memory[VIRTUAL_MEMORY_SIZE][4];
char real_memory[REAL_MEMORY_SIZE][4];
char input_data[100][4]; 
int page_table[TOTAL_PAGES]; 
int page_address=0;
PCB pcb; 
int IC = 0; 
char IR[4]; 
char GPR[4]; 
bool C = false; 
int input_pointer = 0; 

// Interrupt flags
int SI = NO_INTERRUPT; 
int TI = NO_INTERRUPT;  
int PI = NO_INTERRUPT; 

FILE *input_fp, *output_fp;

int main() {
    srand(time(NULL)); 

    init(); 

    FILE *fptr = fopen("OSinput.txt", "r");
    if (!fptr) {
        printf("Error: can't open the input file\n");
        return 0;
    }

    output_fp = fopen("OSoutput.txt", "w");
    if (!output_fp) {
        printf("Error: can't open the output file\n");
        return 0;
    }

    load_program_from_file(fptr);
    fclose(fptr);

    printf("Loaded memory (Real Memory):\n");
    fclose(output_fp);
    print_memory();

    return 0;
}

void init() {
    for (int i = 0; i < REAL_MEMORY_SIZE; i++) {
        for (int j = 0; j < 4; j++) {
            real_memory[i][j] = ' ';
        }
    }

    for (int i = 0; i < VIRTUAL_MEMORY_SIZE; i++) {
        for (int j = 0; j < 4; j++) {
            virtual_memory[i][j] = ' ';
        }
    }
    for (int i = 0; i < TOTAL_PAGES; i++) {
        page_table[i] = -1; 
    }
    pcb.job_id = 0;
    pcb.ttl = 0;
    pcb.tll = 0;
    pcb.PTR = -1; 
    pcb.TTC = 0;  
    pcb.LLC = 0;  
}

void load_program_from_file(FILE *fptr) {
    char line[45];
    bool buffer_filled = false;
    bool data_section = false;

    while (fgets(line, sizeof(line), fptr)) {
        printf("--->line : %s\n",line);
        if (strncmp(line, "$AMJ", 4) == 0) {
            sscanf(line, "$AMJ %4d %4d %4d", &pcb.job_id, &pcb.ttl, &pcb.tll);
            printf("Control Card: Job ID: %04d, TTL: %04d, TLL: %04d\n", pcb.job_id, pcb.ttl, pcb.tll);
            pcb.PTR = generate_random_block(); 
            printf("Page Table Register (PTR) initialized to real memory block: %d\n", pcb.PTR);
        } else if (strncmp(line, "$DTA", 4) == 0) {
            printf("Data section starts. Program card loaded into memory, ready to start execution.\n");
            data_section = true; 
        } else if (strncmp(line, "$END", 4) == 0) {
            printf("End of Job detected.\n");
            break;
        } else {
            if (!data_section && !buffer_filled) {
                // Load program card into buffer before $DTA
                strncpy(buffer, line, sizeof(buffer));
                printf("Program card loaded into buffer: %s\n", buffer);
                load_program_from_buffer_to_virtual_memory();
            } else if (data_section) {
                printf("\nStarting program execution...\n");
//Execution:
                    while (IC < 20) {
                        int RA;
                        address_map(IC, &RA); 

                        strncpy(IR, real_memory[RA], 4);
                        printf("Executing instruction '%s' at Real Address %d (Virtual Address %d)\n", IR, RA, IC);

                        if (pcb.TTC > pcb.ttl) {
                            TI = TI_TIMEOUT;
                        }

                        // Master mode instructions
                        if (strncmp(IR, "H", 1) == 0) {
                            printf("Executing Master Mode Instruction: Halt (H)\n");
                            SI = SI_HALT;
                            break;
                        } else if (strncmp(IR, "GD", 2) == 0) {
                            int gd_address;
                            sscanf(IR + 2, "%d", &gd_address);
                            printf("Executing Master Mode Instruction:GD %d\n",gd_address);
                            strncpy(virtual_memory[gd_address], line, 4); 
                            printf("Reaading data: %s\n",virtual_memory[gd_address]);
                            store_instruction_in_real_memory(gd_address,virtual_memory[gd_address]);
                            SI = SI_READ;

                            pcb.LLC++; 

                                if (pcb.LLC > pcb.tll) {
                                    TI = TI_TIMEOUT;
                                }
                            break;
                        } else if (strncmp(IR, "PD", 2) == 0) {
                            printf("Executing Master Mode Instruction: Print Data (PD)\n");
                            int pd_address;
                            sscanf(IR + 2, "%d", &pd_address);
                            handle_PD(pd_address); 
                            SI = SI_WRITE;
                        }
                        // Slave mode instructions
                        else if (strncmp(IR, "LR", 2) == 0) {
                            printf("Executing Slave Mode Instruction: Load Register (LR)\n");
                            int lr_address;
                            sscanf(IR + 2, "%d", &lr_address);
                            load_register(lr_address); 
                        } else if (strncmp(IR, "SR", 2) == 0) {
                            printf("Executing Slave Mode Instruction: Store Register (SR)\n");
                            int sr_address;
                            sscanf(IR + 2, "%d", &sr_address);
                            store_register(sr_address); 
                        } else if (strncmp(IR, "CR", 2) == 0) {
                            printf("Executing Slave Mode Instruction: Compare Register (CR)\n");
                            int cr_address;
                            sscanf(IR + 2, "%d", &cr_address);
                            compare_register(cr_address); 
                        } else if (strncmp(IR, "BT", 2) == 0) {
                            printf("Executing Slave Mode Instruction: Branch if True (BT)\n");
                            int bt_address;
                            sscanf(IR + 2, "%d", &bt_address);
                            branch_if_true(bt_address); 
                        } else {
                            printf("Invalid Operation Code Detected!\n");
                            PI = PI_INVALID_OPCODE; 
                        }

                        interrupt_handler(SI, TI, PI);

                        IC++; 
                        pcb.TTC++; 
                    }
                            }
                    //         if(SI = SI_HALT){
                    //     break;
                    // }
                        }
                    }
}

void load_program_from_buffer_to_virtual_memory() {
    int virtual_address = 0;
    for (int i = 0; i < sizeof(buffer); i += 4) {
        if (virtual_address < VIRTUAL_MEMORY_SIZE) {
            char instruction[4];
            strncpy(instruction, buffer + i, 4);
            store_instruction_in_real_memory(virtual_address, instruction);
            virtual_address++;
        }
    }
    printf("Program card loaded from buffer to virtual memory and real memory.\n");
}

void store_instruction_in_real_memory(int VA, char* instruction) {
    int RA;
    address_map(VA, &RA); 

    strncpy(real_memory[RA], instruction,10);
    // print_memory();
    printf("Stored instruction '%s' at Real Memory Address: %d\n", instruction, RA);
    update_page_table(VA, RA); 
}

void address_map(int VA, int *RA) {
    int page_number = VA / PAGE_SIZE;
    int page_offset = VA % PAGE_SIZE;

    if (page_table[page_number] == -1) {
        page_table[page_number] = generate_random_block();
    }
    *RA = page_table[page_number] * PAGE_SIZE + page_offset;
    printf("Page %d mapped to Real Memory Block %d ,address %d\n", page_number, page_table[page_number],*RA);
}

int generate_random_block() {
    return rand() % (REAL_MEMORY_SIZE / PAGE_SIZE); 
}

void update_page_table(int VA, int RA) {
    int page_number = VA / PAGE_SIZE;
    if (page_table[page_number] == -1) {
        page_table[page_number] = RA / PAGE_SIZE;
        real_memory[pcb.PTR*PAGE_SIZE + page_address];
        page_address++;
        printf("Updated Page Table: Virtual Page %d mapped to Real Memory Block %d\n", page_number, page_table[page_number]);
    }
}


void handle_PD(int address) {
    // Simulate writing data to output
    fprintf(output_fp, "%s\n", address, virtual_memory[address]);
    printf("Wrote data from virtual memory address %d to output file: %s\n", address, virtual_memory[address]);
    
}

void interrupt_handler(int SI, int TI, int PI) {
    if (PI == PI_INVALID_OPCODE) {
        printf("Program Interrupt: Invalid Opcode. Terminating Job.\n");
        exit(1); 
    } else if (PI == PI_INVALID_PAGE) {
        printf("Program Interrupt: Invalid Memory Access.\n");
        exit(1); 
    } else if (TI == TI_TIMEOUT) {
        printf("Time Interrupt: Time Limit Exceeded.\n");
        exit(1);
    } else if (SI == SI_HALT) {
        printf("Program halted by Supervisor.\n");
        exit(0); 
    }
}

void load_register(int address) {
    printf("Loading data from virtual memory address %d into GPR\n", address);
    strncpy(GPR, virtual_memory[address], 4);
}

void store_register(int address) {
    printf("Storing data from GPR into virtual memory address %d\n", address);
    strncpy(virtual_memory[address], GPR, 4);
}

void compare_register(int address) {
    printf("Comparing GPR with virtual memory at address %d\n", address);
    if (strncmp(GPR, virtual_memory[address], 4) == 0) {
        C = true;
        printf("Comparison successful: GPR == Memory\n");
    } else {
        C = false;
        printf("Comparison failed: GPR != Memory\n");
    }
}

void branch_if_true(int address) {
    if (C) {
        IC = address;
        printf("Branch taken: IC set to %d\n", IC);
    } else {
        printf("Branch not taken: C is false\n");
    }
}

void print_memory() {
    for (int i = 0; i < REAL_MEMORY_SIZE; i++) {
        printf("%d: ", i);
        for (int j = 0; j < 4; j++) {
            printf("%c", real_memory[i][j]);
        }
        printf("\n");
    }
}