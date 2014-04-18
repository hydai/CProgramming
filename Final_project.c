/* @Final_project.c
 * Author: PIatan
 * Date: 2013/1/17
 * Description: cu
 */
#include <stdio.h>
#include <stdlib.h>

//OP_defined
#define OP_ADD  0x1 //0b0001
#define OP_AND  0x5 //0b0101
#define OP_BR   0x0 //0b0000
#define OP_JMP  0xC //0b1100
#define OP_JSR  0x4 //0b0100
#define OP_JSRR 0x20//0b0100000
#define OP_LD   0x2 //0b0010
#define OP_LDI  0xA //0b1010
#define OP_LDR  0x6 //0b0110
#define OP_LEA  0xE //0b1110
#define OP_NOT  0x9 //0b1001
#define OP_ST   0x3 //0b0011
#define OP_STI  0xB //0b1011
#define OP_STR  0x7 //0b0111
#define OP_TRAP 0xF //0b1111
#define OP_RET  0xC1C0
#define OP_HALT 0xD //0b1101

//POINT_defined
#define ENTRY_POINT 0x30
#define END_POINT 0x0

//TYPE_defined
typedef unsigned short u16;

struct vcpu {
	u16 reg[8];
	u16 PC;
};
struct operand {
	int dst;
	int src1;
	int src2;
	int baser;
	int NZP;
	u16 offset;
};
int LAST_REG = 0;
struct vcpu vcpu;
u16 memory[0x80];

//FUNCTION_defined
//GET_offset6
static u16 get_offset6(u16 offset)
{
        if ((offset >> 5) & 0x1) {
            return (offset | 0xFFD0);
        }
    return offset;
}
//GET_offset9
static u16 get_offset9(u16 offset)
{
    if ((offset >> 8) & 0x1) {
        return (offset | 0xFE00);
    }
    return offset;
}
//GET_offset11
static u16 get_offset11(u16 offset)
{
    if ((offset >> 10) & 0x1) {
        return (offset | 0xF800);
    }
    return offset;
}
//GET_imm5
static u16 get_imm5(u16 offset)
{
        if ((offset >> 4) & 0x1) {
            return (offset | 0xFFE0);
        }
    return offset;
}
//NOT
static void store_not(u16 value_to_be_stored, struct operand operand)
{
	vcpu.reg[operand.dst] = value_to_be_stored;
	LAST_REG = operand.dst;
}

static u16 exec_not(struct operand operand)
{
	return (~vcpu.reg[operand.src1]);
}

static struct operand fetch_not_operand(u16 instr)
{
	struct operand operand;
	operand.src1 = ((instr >> 6) & 0x7);
	operand.dst = ((instr >> 9) & 0x7);

	return operand;
}

static void emu_not(u16 instr)
{
	struct operand operand = fetch_not_operand(instr);
	u16 value_to_be_stored = exec_not(operand);
	store_not(value_to_be_stored, operand);
}

//ADD
static void store_add(u16 value_to_be_stored, struct operand operand)
{
	vcpu.reg[operand.dst] = value_to_be_stored;
	LAST_REG = operand.dst;
}
static u16 exec_add(struct operand operand, u16 instr)
{
        u16 bit5 = ((instr >> 5) & 0x1);
        u16 imm5;
        if (bit5 == 0x0) {
            return (vcpu.reg[ operand.src1 ] + vcpu.reg[ operand.src2 ]);
        }
        else {
            imm5 = get_imm5(operand.offset);

            //if true --> imm5 is nogetive
            if ((imm5 >> 5) & 0x1) {
                return (vcpu.reg[ operand.src1 ] - (~imm5 + 1));
                
            }
            else {
                return (vcpu.reg[ operand.src1 ] + imm5);
            }
        }
}
static struct operand fetch_add_operand(u16 instr)
{
        struct operand operand;
        u16 bit5 = ((instr >> 5) & 0x1);

        if (bit5 == 0x0) {
            operand.src2 = (instr & 0x7);
            operand.src1 = ((instr >> 6) & 0x7);
            operand.dst  = ((instr >> 9) & 0x7);
        }
        else {
            operand.src1 = ((instr >> 6) & 0x7);
            operand.dst  = ((instr >> 9) & 0x7);
            operand.offset = (instr & 0x1F);
        }

        return operand;
}
static void emu_add(u16 instr)
{
        struct operand operand = fetch_add_operand(instr);
        u16 value_to_be_stored = exec_add(operand, instr);
        store_add(value_to_be_stored, operand);
}

//AND
static void store_and(u16 value_to_be_stored, struct operand operand)
{
	vcpu.reg[operand.dst] = value_to_be_stored;
	LAST_REG = operand.dst;
}
static u16 exec_and(struct operand operand, u16 instr)
{
        u16 bit5 = ((instr >> 5) & 0x1);
        u16 imm5;
        if (bit5 == 0x0) {
            return (vcpu.reg[ operand.src1 ] & vcpu.reg[ operand.src2 ]);
        }
        else {
            imm5 = get_imm5(operand.offset);
            return (vcpu.reg[ operand.src1 ] & imm5);
        }
}
static struct operand fetch_and_operand(u16 instr)
{
        struct operand operand;
        u16 bit5 = ((instr >> 5) & 0x1);

        if (bit5 == 0x0) {
            operand.src2 = (instr & 0x7);
            operand.src1 = ((instr >> 6) & 0x7);
            operand.dst  = ((instr >> 9) & 0x7);
        }
        else {
            operand.src1 = ((instr >> 6) & 0x7);
            operand.dst  = ((instr >> 9) & 0x7);
            operand.offset = (instr & 0x1F);
        }

        return operand;
}
static void emu_and(u16 instr)
{
        struct operand operand = fetch_and_operand(instr);
        u16 value_to_be_stored = exec_and(operand, instr);
        store_and(value_to_be_stored, operand);
}
//LD
static void load_ld(u16 value_to_be_loaded, struct operand operand)
{
        vcpu.reg[ operand.dst ] = memory[value_to_be_loaded];
        LAST_REG = operand.dst;
}
static u16 exec_ld(struct operand operand)
{
        u16 offset9 = get_offset9(operand.offset);
        //if true, offset9 is nogetive
        if ((offset9 >> 9) & 0x1) {
            return (vcpu.PC - (~offset9 + 1));
        }
        else {
            return (vcpu.PC + offset9);
        }
}
static struct operand fetch_ld_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.dst = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_ld(u16 instr)
{
        struct operand operand = fetch_ld_operand(instr);
        u16 value_to_be_loaded = exec_ld(operand);
        load_ld(value_to_be_loaded, operand);
}
//LDI
static void load_ldi(u16 value_to_be_loaded_point, struct operand operand)
{
        vcpu.reg[ operand.dst ] = memory[memory[value_to_be_loaded_point]];
        LAST_REG = operand.dst;
}
static u16 exec_ldi(struct operand operand)
{
        u16 offset9 = get_offset9(operand.offset);
        //if true, offset9 is nogetive
        if ((offset9 >> 9) & 0x1) {
            return (vcpu.PC - (~offset9 + 1));
        }
        else {
            return (vcpu.PC + offset9);
        }
}
static struct operand fetch_ldi_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.dst = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_ldi(u16 instr)
{
        struct operand operand = fetch_ldi_operand(instr);
        u16 value_to_be_loaded_point = exec_ldi(operand);
        load_ldi(value_to_be_loaded_point, operand);
}
//LDR
static void load_ldr(u16 value_to_be_loaded, struct operand operand)
{
        vcpu.reg[ operand.dst ] = value_to_be_loaded;
        LAST_REG = operand.dst;
}
static u16 exec_ldr(struct operand operand)
{
        u16 offset6 = get_offset6(operand.offset);
        //if true, offset9 is nogetive
        if ((offset6 >> 6) & 0x1) {
            return (memory[operand.baser - (~offset6 + 1)]);
        }
        else {
            return (memory[operand.baser + offset6]);
        }
}
static struct operand fetch_ldr_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x3F);
        operand.dst = ((instr >> 9) & 0x7);
        operand.baser = ((instr >> 6) & 0x7);
        return operand;
}
static void emu_ldr(u16 instr)
{
        struct operand operand = fetch_ldr_operand(instr);
        u16 value_to_be_loaded = exec_ldr(operand);
        load_ldr(value_to_be_loaded, operand);
}
//LEA
static void load_lea(u16 value_to_be_loaded_point, struct operand operand)
{
        vcpu.reg[ operand.dst ] = value_to_be_loaded_point;
        LAST_REG = operand.dst;
}
static u16 exec_lea(struct operand operand)
{
        u16 offset9 = get_offset9(operand.offset);
        //if true, offset9 is nogetive
        if ((offset9 >> 9) & 0x1) {
            return (vcpu.PC - (~offset9 + 1));
        }
        else {
            return (vcpu.PC + offset9);
        }
}
static struct operand fetch_lea_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.dst = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_lea(u16 instr)
{
        struct operand operand = fetch_lea_operand(instr);
        u16 value_to_be_loaded = exec_lea(operand);
        load_lea(value_to_be_loaded, operand);
}
//ST
static void store_st(u16 value_to_be_stored_point, struct operand operand)
{
        memory[value_to_be_stored_point] = vcpu.reg[ operand.dst ];
 }
static u16 exec_st(struct operand operand)
{
        u16 offset9 = get_offset9(operand.offset);
        //if true, offset9 is nogetive
        if ((offset9 >> 9) & 0x1) {
            return (vcpu.PC - (~offset9 + 1));
        }
        else {
            return (vcpu.PC + offset9);
        }
}
static struct operand fetch_st_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.dst = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_st(u16 instr)
{
        struct operand operand = fetch_st_operand(instr);
        u16 value_to_be_stored_point = exec_st(operand);
        store_st(value_to_be_stored_point, operand);
}
//STI
static void store_sti(u16 value_to_be_stored_point, struct operand operand)
{
        memory[memory[value_to_be_stored_point]] = vcpu.reg[ operand.dst ];
}
static u16 exec_sti(struct operand operand)
{
        u16 offset9 = get_offset9(operand.offset);
        //if true, offset9 is nogetive
        if ((offset9 >> 9) & 0x1) {
            return (vcpu.PC - (~offset9 + 1));
        }
        else {
            return (vcpu.PC + offset9);
        }
}
static struct operand fetch_sti_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.dst = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_sti(u16 instr)
{
        struct operand operand = fetch_sti_operand(instr);
        u16 value_to_be_stored_point = exec_sti(operand);
        store_sti(value_to_be_stored_point, operand);
}
//STR
static void store_str(u16 value_to_be_stored_point, struct operand operand)
{
        memory[value_to_be_stored_point] = vcpu.reg[ operand.dst ];
}
static u16 exec_str(struct operand operand)
{
        u16 offset6 = get_offset6(operand.offset);
        //if true, offset9 is nogetive
        if ((offset6 >> 6) & 0x1) {
            return (operand.baser - (~offset6 + 1));
        }
        else {
            return (operand.baser + offset6);
        }
}
static struct operand fetch_str_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x3F);
        operand.dst = ((instr >> 9) & 0x7);
        operand.baser = ((instr >> 6) & 0x7);
        return operand;
}
static void emu_str(u16 instr)
{
        struct operand operand = fetch_str_operand(instr);
        u16 value_to_be_stored_point = exec_str(operand);
        store_str(value_to_be_stored_point, operand);
}
//TRAP
static void interrupt_trap(u16 trapvect, struct operand operand)
{
        vcpu.PC = memory[trapvect];
}
static u16 exec_trap(struct operand operand)
{
        u16 trapvect = operand.offset;
        vcpu.reg[7] = vcpu.PC;
        return trapvect;
}
static struct operand fetch_trap_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0xFF);
        return operand;
}
static void emu_trap(u16 instr)
{
        struct operand operand = fetch_trap_operand(instr);
        u16 trapvect = exec_trap(operand);
        interrupt_trap(trapvect, operand);
}
//RET
static void emu_ret(u16 instr)
{
        vcpu.PC = vcpu.reg[7];
}
//JMP
static void emu_jmp(u16 instr)
{
        u16 baser = ((instr >> 6) & 0x7);
        vcpu.PC = vcpu.reg[baser];
}
//JSR
static void branch_jsr(u16 PCoffset)
{
        vcpu.reg[7] = vcpu.PC;
        vcpu.PC = PCoffset;
}
static u16 exec_jsr(struct operand operand)
{
        u16 offset11 = get_offset11(operand.offset);
        if ((offset11 >> 11) & 0x1) {
            return (vcpu.PC - (~offset11 + 1));
        }
        else {
            return (vcpu.PC + offset11);
        }
}
static struct operand fetch_jsr_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x7FF);
        return operand;
}
static void emu_jsr(u16 instr)
{
        struct operand operand = fetch_jsr_operand(instr);
        u16 PCoffset = exec_jsr(operand);
        branch_jsr(PCoffset);
}
//JSRR
static void branch_jsrr(struct operand operand)
{
        vcpu.reg[7] = vcpu.PC;
        vcpu.PC = operand.baser;
}
static struct operand fetch_jsrr_operand(u16 instr)
{
        struct operand operand;
        operand.baser = ((instr >> 6) & 0x7);
        return operand;
}
static void emu_jsrr(u16 instr)
{
        struct operand operand = fetch_jsrr_operand(instr);
        branch_jsrr(operand);
}
//BR
static void branch_br(struct operand operand)
{
        u16 PCoffset = get_offset9(operand.offset);
        int flag = 0;

        if (operand.NZP == 0) {
            return ;
        }
        else if ((operand.NZP == 1) && (vcpu.reg[LAST_REG] > 0)) {
            flag = 1;
        }
        else if ((operand.NZP == 2) && (vcpu.reg[LAST_REG] == 0)) {
            flag = 1;
        }
        else if ((operand.NZP == 3) && ((vcpu.reg[LAST_REG] > 0) || (vcpu.reg[LAST_REG] == 0))) {
            flag = 1;
        }
        else if ((operand.NZP == 4) && (vcpu.reg[LAST_REG] < 0)) {
            flag = 1;
        }
        else if ((operand.NZP == 5) && ((vcpu.reg[LAST_REG] > 0) || (vcpu.reg[LAST_REG] < 0))) {
            flag = 1;
        }
        else if ((operand.NZP == 6) && ((vcpu.reg[LAST_REG] < 0) || (vcpu.reg[LAST_REG] == 0))) {
            flag = 1;
        }
        else if (operand.NZP == 7) {
            flag = 1;
        }

        if (flag) {
            if ((PCoffset >> 9) & 0x1) {
                vcpu.PC = vcpu.PC - (~PCoffset + 1);
            }
            else {
                vcpu.PC = vcpu.PC + PCoffset;
            }
        }
}
static struct operand fetch_br_operand(u16 instr)
{
        struct operand operand;
        operand.offset = (instr & 0x1FF);
        operand.NZP = ((instr >> 9) & 0x7);
        return operand;
}
static void emu_br(u16 instr)
{
        struct operand operand = fetch_br_operand(instr);
        branch_br(operand);
}
//PRINT 
static void print_memory(FILE *out)
{
	for (int i = 0; i < 0x30; i+=4) {
		fprintf(out, "memory[0x%2x]=%4x, ", i, memory[i]);
		fprintf(out, "memory[0x%2x]=%4x, ", i+1, memory[i+1]);
		fprintf(out, "memory[0x%2x]=%4x, ", i+2, memory[i+2]);
		fprintf(out, "memory[0x%2x]=%4x\n", i+3, memory[i+3]);
	}
	fprintf(out, "======================================\n");
}

static void print_regs(FILE *out)
{
	fprintf(out, "======================================\n");
	fprintf(out, "PC = %2x\n\n", vcpu.PC);

	for (int i = 0; i < 8; ++i) {
		fprintf(out, "reg[%d]=%4x\n", i, vcpu.reg[i]);
	}
}

static u16 decode(u16 instr)
{
    
        if (instr == END_POINT) {
            return OP_HALT;
        }
     
        if (instr == OP_RET) {
            return OP_RET;
        }
        if ((instr >> 9) == OP_JSRR) {
            return OP_JSRR;
        }

	return	(instr >> 12);
}

static u16 fetch(u16 PC)
{
        return memory[PC];
}

void loader(const char bin[])
{
        FILE *fp;
        int i = 0;
        fp = fopen(bin, "rb");
        if (fp == NULL) {
            exit(1);
        }
        while(fread(&memory[ENTRY_POINT+i], sizeof(u16), 1, fp) && !feof(fp))
        {
            i++;
            //printf("%d\n", memory[ENTRY_POINT+i-1]);
        }
        fclose(fp);
}

int main(int argc, char const *argv[])
{
    
	u16 instr;
	u16 op;
	FILE *fout;
	fout = fopen(argv[2], "w");
	/* 
	 * Mask loader part.
	 * You have to do it by yourself.
	 */
	loader(argv[1]); 

	vcpu.PC = ENTRY_POINT;
	do {
		instr = fetch(vcpu.PC);
		vcpu.PC = vcpu.PC + 1;
		/* 
	 	 * Mask fetch part.
		 * You have to do it by yourself.
		 */
        //printf("%d\n", instr);
		op = decode(instr);
        	// Case by case, we only show you NOT instruction.
		if (op == OP_HALT) {
			break;
		}
		else if (op == OP_RET) {
		    emu_ret(instr);
		}
		else if (op == OP_JSRR) {
		    emu_jsrr(instr);
		}
		else if (op == OP_ADD) {
		    emu_add(instr);
		}
		else if (op == OP_AND) {
		    emu_and(instr);
		}
		else if (op == OP_BR) {
		    emu_br(instr);
		}
		else if (op == OP_JMP) {
		    emu_jmp(instr);
		}
		else if (op == OP_JSR) {
		    emu_jsr(instr);
		}
		else if (op == OP_LD) {
		    emu_ld(instr);
		}
		else if (op == OP_LDI) {
		    emu_ldi(instr);
		}
		else if (op == OP_LDR) {
		    emu_ldr(instr);
		}
		else if (op == OP_LEA) {
		    emu_lea(instr);
		}
		else if (op == OP_NOT) {
		    emu_not(instr);
		}
		else if (op == OP_ST) {
		    emu_st(instr);
		}
		else if (op == OP_STI) {
		    emu_sti(instr);
		}
		else if (op == OP_STR) {
		    emu_str(instr);
		}
		else if (op == OP_TRAP) {
		    emu_trap(instr);
		}

		print_regs(fout);
		print_memory(fout);
	} while(1);
	fclose(fout);
	return 0;
}
