### Load and store
- LDA: load accumulator
- LDX: Load X
- LDY: Load Y
- STA: Store accumulator
- STX: Store X
- STY: Store Y

### Arithmetic instructions
- ADC: Add to accumulator with Carry
- SBC: Subtract from accumulator with Carry

### Increment and decrement
- INC: Increment memory by one
- INX: Increment X by one
- INY: Increment Y by one
- DEC: Decrement memory
- DEX: Decrement X
- DEY: Decrement Y

### Bitwise logic
- AND: AND memory with accumulator
- ORA: OR memory with accumulator
- EOR: Exclusive-OR memory with accumulator

### Flow control
- JMP: Goto
- BCC: Branch on Carry clear
- BCS: Branch on Carry set
- BEQ: Branch on Zero set (equal zero)
- BNE: Branch on Zero clear (Not equal zero)
- BMI: Branch on Minus
- BPL: Branch on plus
- BVS: Branch on overflow set
- BVC: Branch on overflow clear

- CMP: Compare memory and accumulator
- CPX: Compare memory and X
- CPY: Compare memory and Y 

- BIT: AND accumulator and memory. V gets bit 6 of memory, N gets bit 7 of memory

### Shift and rotate
- ASL: Accumulator shift left
- LSR: Logical shift right
- ROL: Rotate left
- ROR: Rotate right

### Stack operations
- TSX: Transfer stack pointer to X
- TXS: Transfer X to stack pointer

- PHA: Push accumulator on stack
- PHP: Push processor status on stack
- PLA: Pull accumulator from stack
- PLP: Pull processor status from stack

### Subroutine control
- JSR: Jump to subroutine
- RTS: Return from subroutine
- RTI: Return from interrupt

### Flag Control
- CLC: Clear carry flag
- CLD: Clear decimal mode
- CLI: Clear interrupt disable
- CLV: Clear overflow flag

- SEC: Set carry
- SED: Set decimal mode
- SEI: Set interrupt disable

### Other instructions
- NOP: No Op
- BRK: forced break (software interrupt)