
# WIC Virtual Machine

"WIC" stands for Wren Intermediate Code, which is an intermediate
language for the Wren teaching language. This is a small "virtual
machine" that runs that intermediate language. 

## Use
To use, just run 
    ./wici <code.wic>
	
## About WIC
WIC is a very simple, stack-based intermediate language. The only
types supported are signed integers and Boolean values (which
implemented as integers). 

### Flow Control
The `halt` opcode stops the machine.

Labels are defined in the form `L1 label` (Where 1 can be replaced
with any number). 

Jump statements are in the form `j L1`, where L1 can be any label. The
two forms of the jump instruction are:

- `j` - Jump unconditionally
- `jf` - Jump if value on the top of the stack is false (0). This pops
  that value off the top of the stack. 
  
The `nop` instruction does nothing. 

### Test statements
Test statements pop the a value off the top of the stack and compare
it with zero, pushing either 1 (true) or 0 (false) back on to the
stack. The six test instructions are:

- `tsteq` - equals
- `tstne` - not equals
- `tstlt` - less than
- `tstle` - less than or equal
- `tstgt` - greater than
- `tstge` - greater than or equal

### Math and Logic 
The available mathematical instructions are `add`, `sub`, `mul`,
`div`, and `mod`. They first pop the right operand off the stack, then
pop the left operand, perform the operation, and finally push the
result back on the stack. 

The logical `and` and `or` instructions work the same way. 

The logical `not` instruction is similar, except it only pops a single
value off the stack. 

### Stack instructions
The push instruction is of the form `push A` where A is a variable
name. It pushes the value of the variable A onto the stack. 

The pop instruction is similar -- `pop A` -- except that it pops a
value off of the stack and stores it into variable A. 

### I/O
The `get A` instruction prompts the user `enter A > ` and stores the
inputted number in the variable A.

The `put A` instruction prints `A = 123` where 123 is the value stored
in A. 


