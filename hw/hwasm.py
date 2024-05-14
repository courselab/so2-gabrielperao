import sys
from enum import Enum


class Instruction(str, Enum):
    MOV = "mov",
    HLT = "hlt",
    INT = "int",
    JMP = "jmp",
    WORD = ".word",
    FILL = ".fill",
    END = "#"
    
    def __str__(self):
        return self.value


class CharHandler:
    @staticmethod
    def handle_char_value(val: str):
        val = val.replace(',', '').replace('\'', '')
        return val.encode('utf-8')


class HexadecimalHandler:
    @staticmethod
    def handle_hexadecimal_value(val):
        val = val.replace(',', '')

        if len(val) > 4:
            first_hex = int(val[:4], 16)
            second_hex = int('0x' + val[4:], 16)
            return bytes([second_hex, first_hex])

        hex_value = int(val.replace(',', ''), 16)
        return bytes([hex_value])


class OpcodeHandler:
    @staticmethod
    def get_register_mov_opcode(reg):
        if reg == 'al':
            return bytes([176])
        elif reg == 'ah':
            return bytes([180])


class InstructionConverter:
    @staticmethod
    def convert_instruction_mov(instructions, index):
        val = instructions[index + 1].replace('$', '')
        reg = instructions[index + 2].replace('%', '')

        if reg[0] == '\'':
            val = '\' \','
            reg = instructions[index + 3].replace('%', '')

        prefix = val[0]
        if prefix == '\'':
            val = CharHandler.handle_char_value(val)
        if prefix == '0':
            val = HexadecimalHandler.handle_hexadecimal_value(val)

        reg = OpcodeHandler.get_register_mov_opcode(reg)

        return reg + val
        
    @staticmethod
    def convert_instruction_hlt():
        return bytes([244])

    @staticmethod
    def convert_instruction_int(instructions, index):
        val = instructions[index + 1].replace('$', '')
        val = HexadecimalHandler.handle_hexadecimal_value(val)
        
        opcode = bytes([205])
        return opcode + val

    @staticmethod
    def convert_instruction_jmp(instructions, index):
        return bytes([235, 253])
    

    @staticmethod
    def convert_instruction_word(instructions, index):
        return HexadecimalHandler.handle_hexadecimal_value(instructions[index + 1].replace('$', ''))


class Main:
    @staticmethod
    def main():
        argv = sys.argv
        input_filename = argv[1]
        output_filename = argv[2]

        input_file = open(input_filename, "r")
        output_file = open(output_filename, "wb")
        line = input_file.readline()
        while line:
            line = line.rstrip()
            instructions = line.split()

            for index, instruction in enumerate(instructions):

                if instruction == Instruction.MOV:
                    binary = InstructionConverter.convert_instruction_mov(instructions, index)
                    output_file.write(binary)
                elif instruction == Instruction.HLT:
                    binary = InstructionConverter.convert_instruction_hlt()
                    output_file.write(binary)
                elif instruction == Instruction.INT:
                    binary = InstructionConverter.convert_instruction_int(instructions, index)
                    output_file.write(binary)
                elif instruction == Instruction.JMP:
                    binary = InstructionConverter.convert_instruction_jmp(instructions, index)
                    output_file.write(binary)
                elif instruction == Instruction.WORD:
                    binary = InstructionConverter.convert_instruction_word(instructions, index)
                    output_file.write(binary)
                elif instruction == Instruction.FILL:
                    output_file.write(bytes(461))
                elif instruction == Instruction.END:
                    break

            line = input_file.readline()

        input_file.close()
        output_file.close()

if __name__ == '__main__':
    Main.main()
