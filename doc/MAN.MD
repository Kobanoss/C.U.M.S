	# DOCUMENTATION FOR C.U.M.S.

## BASE OPERATIONS LIST

#### OP_DROP -> `drop`

		Removing integer value from top of the stack.

- Args:

		None
- Input: 

		Element from top of the stack.
- Output: 

		None

- Error:

		Throw UnderFlowError if `drop` called in empty stack.
Example:

	// Add 5, 4, 3 to top of the stack
	5 4 3
	// Remove 5 from top of the stack
	drop
	// On stack -> 4 3 	
---

#### OP_DUP -> `dup`



	Duplicate value on the top of the stack.
- Args:

		None
- Input: 

		Takes from stack
- Output: 

		- Push back to stack: 
- Error:

		Throw UnderFlow Error if stack is empty.
Example:

	5  4  // Push 5 to top of the stack. Stack contains only 5, 4
	dup  // Duplicate 5. Stack now contains [5, 4, 4]


---

#### OP_DUPM -> `dupm`



	Duplicate n-values on the top of the stack.
- Args:

		None
- Input: 

		Takes from stack: 
- Output: 

		Integer (Number of elements)[N], Copy of n-integers
- Error:

		Throw UnderFlow Error if stack is empty.
.
Example:

	5 10 15 // Push 5, 10, 15 to top of the stack. Stack contains [5, 10, 15]
	2 dupm  // Duplicate 10, 15. Stack now contains [5, 10, 15, 10, 15]
	

---

#### OP_OVER -> `over`



	Duplicate 1 element over current (»this«, current).
- Args:

		None
- Input: 

		Copy of 1 element over current   
- Output: 

		Push that element to top of the stack
- Error:

		Stack underflow.
Example:

	1 2  3  // On stack [1, 2, 3] 
	over // On stack [1, 2, 3, 2].

---

#### OP_OVERM -> `overm`



	Removes elements starting from the top of the stack going down as much as 	the user wants.
- Args:

		None
- Input: 

		elements starting from the top of the stack
- Output: 

		None.
- Error:

		Throw StackUnderflow Error if stack have less values, than over-			index.
Example:

	1 2 3 4 5 
	3 overm
	// 1 2 3 4 5 2

---

#### OP_SWAP-> `swap`



	swapping two values at the top of the stack.
- Args:

		none 
- Input: 

		takes two numbers
- Output: 

		returns two numbers in reverse order.
- Error:

		if there are not 2 values on the stack.
Example:

	none
---

#### OP_PLUS -> `+`



	At the end of the stack, it takes two elements and combines them into
	one and push back
- Args:

		None
- Input: 

		Takes 2 integers from top of the stack
- Output: 

		Result of combine 2 elements   
- Error:

		Throw ValueError if values is not integers
		Throw UnderflowError if stack size < 2
Example:

	1 2 2 +
	// 1 4


---

#### OP_MINUS -> `-`



	subtracts the first value from the second.
- Args:

		None
- Input: 

		two numbers
- Output: 

		answer after subtracting two numbers.
- Error:

		if there is no value.
Example:

	1 2 –
	// -1

---

#### OP_MUL -> `*`



	multiplies the first value by the second.
- Args:

		None
- Input: 

		enters two values that it multiplies
- Output: 

		outputs the answer after multiplication.
- Error:

		if there is no value.
Example:

	5 10 *
	// 50

---

#### OP_DIV-> `//`



	Divides the first value by the second.
- Args:

		None
- Input: 

		enters two values that it divides
- Output: 

		outputs the answer after division.
- Error:

		if there is no value.
Example:

	10 5 //
	// 2


---

#### OP_MOD -> `%`



	takes two numbers and returns the remainder of the division 1 by 2.
- Args:

		none 
- Input: 

		takes two numbers.
- Output: 

		returns the remainder.
- Error:

		StackUnderflow if there are no 2 numbers.
Example:

	none
---

#### OP_DEBUG_INT -> `iDebug`



	Outputs the integer element of the top of the stack.
- Args:

		None
- Input: 

		Takes an integer element of the top of the stack
- Output: 

		Outputs the integer element from the top of the stack.
- Error:

		Throw StackUnderflow Error if stack is empty.
Example:

	1 2 3 iDebug

---

#### OP_DEBUG_CHAR -> `cDebug`



	we took a number and interpreted it as a character from the ASCII table.
- Args:

		None
- Input: 

		takes an integer value from the stack
- Output: 

		we get the symbol by this value.
- Error:

		If the value is outside the table, the behavior is undefined
		Stack Underflow error if the stack is empty.
Example:

	-example : 104 cDebug
	//print “h” 

---

#### OP_MEM -> `mem`



	Return memory start pointer.
- Args:

		None
- Input: 

		None
- Output: 

		pointer to a starting address in memory (to zero point).
- Error:

		No Errors.
Example:

	mem 		// 0x123456
	mem 3 + 	// 0x123459    

---

#### OP_MEM_PUSH-> `mPush`



	takes a value from the stack and loads it into memory.
- Args:

		none 
- Input: 

		takes a value from the stack and a point in memory
- Output: 

		none .
- Error:

		StackUnderflow if there are not 2 values on the stack.
Example:

	none
---

#### OP_MEM_LOAD -> `mLoad`



	Push to stack data from point of memory.
- Args:

		None
- Input: 

		Pointer to memory
- Output: 

		Data from the memory cell.
- Error:

		Segmentation fault (core dumped) if nothing in memory.
Example:

	mem 3 + mLoad

---

#### OP_SYSCALL -> `syscall`



	Call Linux system-calls.
- Args:

		None
- Input: 

		Name(Index) of syscall, syscall arguments, number of syscall 
		arguments + 1;
- Output: 

		None.
- Error:

		Throw Stack UnderFlowError if not enough values on stack
		Can throw  SEGFAULT if syscall changes memory. And do it wrong.
Example:

		0 	0 	mem 		10 	4 			syscall 
	//	(name)  (fd)	(pointer)	(size)	(number of args)	(call)


---

#### OP_EQUAL  -> `==`



	takes two numbers from the stack and checks them for equality.
- Args:

		None
- Input: 

		takes two numbers
- Output: 

		returns 1 if the numbers are 0 otherwise.
- Error:

		to do underFlor Error
		in the absence of 2 numbers.
Example:

	// 2 4 == 
	// 0 (on stack)

---

#### OP_NOT_EQUAL-> `!=`



	Takes two values from the stack and compares them, returns 1 if equal
	otherwise 0..
- Args:

		None
- Input: 

		takes two integers
- Output: 

		comparison result.
- Error:

		throws Stack Underflow if there are no two values.
Example:

	none

---

#### OP_GREATER-> ``>``



	takes two values ​​and compares which value is greater.
- Args:

		None
- Input: 

		takes two values
- Output: 

		prints the result of the comparison.
- Error:

		if there are not 2 values on the stack.
Example:

	2 1 >
	//1
	while 2 0 >:
	123
	End
---

#### OP_LOWER -> `>``



	Inputakes two values and compares which value is Lowert.
- Args:

		takes two values
- Input: 

		prints the result of the comparison
- Output: 

		if there are not 2 values on the stack.
- Error:

		throws Stack Underflow if there are no two values.
Example:

	1 2 <
	//1

---

#### OP_IF -> `if`

	Starts the if-block. Should be before condition. Marks condition start point.

- Args:
	
		None
- Input: 
	
		None
- Output: 
		
		None
- Error:

		None
Example:
	
	if 1 2 > :
		4 iDebug
	end
	
// Prints 4

---

#### OP_DO -> `:`

	Starts executing current block based on condition before this operator. (should be 1 or 0). 
	In while-loop it starts executing code in new loop after this operator.
	Should be used after while, if, else.

- Args:
	
		None
- Input: 
	
		None
- Output: 
		
		None
- Error:

		Throw Error if no `if`-block.
Example:
	
	if 1 2 > :
		4 iDebug
	else :
	`	5 iDebug
	end
	
// Prints 5

---

#### OP_ELSE -> `else`

	Marks else-way in condition, can be used in if-block.

- Args:
	
		None
- Input: 
	
		None
- Output: 
		
		None
- Error:

		Throw Error if no `if`-block.
Example:
	
	if 1 2 > :
		4 iDebug
	else :
	`	5 iDebug
	end
	
// Prints 5

---

#### OP_END-> `END`



	completion of a special block (If, while) or some operation.
- Args:

		None
- Input: 

		None
- Output: 

		if there is no start of any block.
- Error:

		None.
Example:

	if 1:
	          1 2 3 4 5
	end

---

#### OP_WHILE -> `while`



	Starts the while-loop(block). Should be before condition. Marks condition 	start point.
- Args:

		None
- Input: 

		None
- Output: 

		None.
- Error:

		None.
Example:

	0 while dup 1 < :
	         1+
	end

---

#### OP_BITSHIFT_LEFT -> `"<<"`



	bit shift operation.
- Args:

		none 
- Input: 

		takes two integers
- Output: 

		the resulting number after the shift.
- Error:

		if he does not see two values, then there will be StackUnderFlow.
Example:

	None
---

#### OP_BITSHIFT_RIGHT -> `">>"`



	bit shift to right operation.
- Args:

		none 
- Input: 

		takes two integers
- Output: 

		the resulting number after the shift.
- Error:

		if he does not see two values, then there will be StackUnderFlow.
Example:

	none

---

#### OP_AND_BIT-> `&`



	Returns the result of the AND bit operation between the first and second value.
- Args:

		None
- Input: 

		Takes 2  values
- Output: 

		returns the result of bitwise and.
- Error:

		throws Stack Underflow if there are no two values.
Example:

	none

---

#### OP_OR_BIT  -> `|`



	compares each bit of the first operand with the corresponding bit of the 
	second operand.
- Args:

		None
- Input: 

		takes two integers
- Output: 

		comparison result.
- Error:

		if there are not 2 values on the stack.
Example:

	none

---

#### OP_MACRO -> `macro`



	prepares for execution a defined set operation by alias.
- Args:

		None
- Input: 

		None
- Output: 

		If there is no macro name, then it will not work.
- Error:

		if there is no macro name.
Example:

	macro
		1 1 2 overm dup strlen 4 syscall endl
		drop
		macroEnd.


---

#### OP_MACRO_END -> `macroEnd`



	Indicates where the end of the macro is.
- Args:

		None
- Input: 

		None
- Output: 

		If there is no beginning of the macro, then there is nothing to end.
- Error:

		if there is no start of the macro.
Example:

	4342
	1 1 2 overm dup strlen 4 syscall endl 
	drop
	macroEnd
---

#### OP_INCLUDE -> `include`



	includes in the program the file that is entered at the beginning.
- Args:

		None
- Input: 

		Takes  NAME OF THE FILE  
- Output: 

		add code from imported file.
- Error:

		gives an error if this file is not valid.
Example:

	None

---
