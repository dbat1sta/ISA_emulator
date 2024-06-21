class RISCV_VM:
    def __init__(self):
        self.registers = [0] * 32 # registers
        self.PC = 0  # Program Counter
        self.memory = [0] * (2**20)  # 1 MiB of RAM

    def read_register(self, reg_num):
        if reg_num == 0:
            return 0
        return self.registers[reg_num]

    def write_register(self, reg_num, value):
        if reg_num != 0:
            self.registers[reg_num] = value

    def sign_extend(self, value, bit_index):
        sign_bit = (value >> bit_index) & 1
        if sign_bit:
            value |= - (1 << bit_index)
        return value

if __name__ == "__main__":
    vm = RISCV_VM()
    print("Virtual Machine Initialized")
