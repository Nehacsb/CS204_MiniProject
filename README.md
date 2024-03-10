# CS204_MiniProject
// Assembler
// Group mumbers :
//  Name : Neha Dahire
//  Name : Radha
//  Name : Sarthak Dev Rathor

In the project, we designed an assembler execution which generates machine code of the data and text segment ressembling to venus simulator.


DATA SEGMENT:
In the data segment the user have to start with assembler directive .data and then define variables with their values represeting as "variable_name: .word 10" without double quotes,where .word is an assembler directive otherwise the code shows error.The user can use other assembler directives instead of .word as .half , .byte , .dword , .asciz .		
NOTE: You can not have two datatypes(assembler directive) for one variable otherwise the machine code terminates showing "Variable declared again error in parsing data segment".Also do not apply commas and give atleast one space after each instruction.Also at the end of one instruction do not give extra spaces.The variable name can be given space within but befor the colon.
The instructions where the user can get error are:
1)For .word assembler directive the user can use decimal,hexadecimal,binary,Characters in such format=> 'C'(instead of C you can take characters with ascii values ranging from 33 and 126 (NOTE: for character with ascii value 39 i.e "'" you should give it in input as => '\'')).The user can not give strings as input in .word otherwise the machine code terminates showing wrong datatype format.
2).half assembler directive use is same as .word
3).byte assembler directive use is same as .half and .word
4)For .asciz assembler directive, the user can give input only one string within double quotes otherwise the machine code terminates showing wrong datatype format.
5)For .dword assembler directive, the user can give input in decimal,hexadecimal,binary formats.The user can not give strings and characters as input in .dword otherwise the machine code terminates showing wrong datatype format.

PRESENTATION OF DATA SEGMENT:
Once the code is executed, the file machine_code.mc will show the data segment with memory address alongwith the data that has stored.
In the venus simulator,.word takes 32 bits , .half takes 16 bits , .byte takes 8 bit, .dword takes 64 bits, .asciz takes (size of string)*8 bits to store their corresponding data.
Our machine code similarly shows the above representation of venus simulator as:
ASSEMBLY LANGUAGE CODE:				         
.data
var: .word 0b11 0x12 'C'
var3: .asciiz "CDE"
var4: .dword 0x343 89
var 5: .half 3
.text
add x3 x4 x2
add x8 x8 x9

GENERATED MACHINE CODE:
0x10000000 0x00000003
0x10000004 0x00000012
0x10000008 0x43

0x1000000C 0x43
0x1000000D 0x44
0x1000000E 0x45
0x1000000F 0x00

0x10000010 0x0000000000000343
0x10000018 0x0000000000000059
0x10000020 0x0003
text segment
0x0  0x002201B3
0x4  0x00940433
0x8  End of code


The machine code is in hexadecimal format(both memory addresses and the data stored).
Also in venus simulator if we use decimal format in .dword then the data stored in memory has some  different format.We have done this part differently as compared to venus and stored the converted form of decimal to hexadecimal.
NOTE: The user cannot use negative hexadecimal and binary numbers(such as -0x12 -0b11) as it is invalid form and the code shows error. 
After data segment, the user has to use assembler directive .text for text segment where instructions are applied.
The user can give either a newline or an instruction just after defining .text.If the user writes an instruction before some label or .text then there is an error.


TEXT_SEGMENT:
In the text segment, we coded for all the stated instructions.We did not support pseudoinstructions in our assembler.The text segment shows the value of PC(PROGRAM COUNTER) alongwith the decoded fields of opcode,funct3,funct7,immediate,rs1,rs2,rd according to the different risc-v formats.
The instructions where the user can get error are:
1)IMMEDIATE FIELD ERRORS: These errors are stored in one string "out" of main function through which we are terminating the code if there is an error. 
  a)WRONG INPUT:The user cannot use negative hexadecimal and binary numbers(such as -0x12 -0b11) as it is invalid form and the code shows "WRONG INPUT".
  b)INVALID OFFSET: Also for the immediate field if the user has entered an offset of the form H126 then it is not hexadecimal,decimal ,binary form,so there is a error mentioned as INVALID OFFSET. If someone tries to use bits other than 0 or 1 in binary then it is an INVALID OFFSET.Similarly for hexadecimal and decimal form.
  c)OUT OF RANGE:If immediate field is not within range (range is different for 12bit immediate value and 20-bit immediate value).
  d)REGISTER NOT FOUND: This can occur if the user has not used x0-x31 registers and instead used some label or other than those mentioned registers.
  e)INSTRUCTION NOT IDENTIFIED: If the user uses the wrong instruction format or wrong instruction name then this can occur.
2)R-format: There is no chance of error but instead if you give more numbers of registers than needed then the first ones are considered and remaining are not taken into consideration.
3)I-format: We have divided this into to functions:I-FORM AND L_I-FORM where instructions such as addi,andi,jalr etc are under I-FORM and lw,lh,lb,ld are in L_I-FORM.
	I-FORM:In this,all errors in 1st point can occur.NOTE:The format of "jalr" instruction in Venus is of the type "x0, offset(x1)", where the offset is treated like an immediate value. However, in Venus, labels can also be used in place of immediate values. But, we are considering only immediate values.
	L_I-FORM:In this,all errors in 1st point can occur.
4)S-FORM:All errors of 1st point can occur.
5)SB and UJ-FORM: In these one error can occur which is LABEL NOT FOUND.

NOTE:Try to use text segment with either one space or comma within registers.We have tried out best to cover all possible cases in which the user can use register after register with any amount of space,comma etc but it is the most convenient way if the user can write instruction registers with one space or comma between them.

We have done coding for the comments also as if the user uses comments starting with # then the whole line after this hashtag(alongwith this hashtag) will not be read by the code and hence they are only used for conveying the functionality of various functions etc.

At the end of text segment there is a termination code to signify this and in turn, there is an end of the assembly program.
