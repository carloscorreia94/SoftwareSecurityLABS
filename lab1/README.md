*LAB 1 - FORMAT STRING VULNERABILITY*

Compile vul_prog with gcc

Solution.
Type in the first value, the decimal address of the memory position you want to infect
Typ in the secound value, witch is going to be injected in the printf dynamically, a limited number of %08x (in our case was 8 times) so that you can overflow the memory(stack) and write over the memory
