# DOCUMENTATION FOR C.U.M.S.



## BASE OPERATIONS LIST.



#### OP_PUSH_INT -> 44







        Push number to stack.







- Args:







        Integer.



- Input: 







        None.



- Output: 







        Integer.







- Error:







        None



Example:



    4





---



#### OP_PUSH_CHAR -> 'm'







        Takes a symbol and outputs it to the stack as a number.







- Args:







        Character.



- Input: 







        None.



- Output: 







        Character according to the ascii table.







- Error:







         Undefined behavior if character is not in ascii table.
         C-Error if there is no argument.



Example:



    'h'







---



#### OP_PUSH_STR -> "Hello"







        Add string to memory and push pointer to it to stack.







- Args:







        String (array of characters).



- Input: 







        None.



- Output: 







        Returns a pointer to string in memory.







- Error:







        C-Error If there is no argument.



Example:



    "Hello"



#### OP_DROP -> `drop`



		Removing integer value from top of the stack.



- Args:



		None.

- Input: 



		Element from top of the stack.

- Output: 



		None.



- Error:



		Throw UnderFlowError if `drop` called in empty stack.

Example:



		// Add 5, 4, 3 to top of the stack

		5 4 3

		// Remove 3 from top of the stack

		drop

		// On stack -> 5 4 	

---



#### OP_DUP -> `dup`







		Duplicate value on the top of the stack.

- Args:



		None.

- Input: 



		Takes from stack.

- Output: 



		- Push back to stack.

- Error:



		Throw UnderFlow Error if stack is empty.

Example:



		5  4  // Push 5 to top of the stack. Stack contains only 5, 4

		dup  // Duplicate 5. Stack now contains [5, 4, 4]





---



#### OP_DUPM -> `dupm`







		Duplicate n-values on the top of the stack.

- Args:



		None.

- Input: 



		Takes from stack.

- Output: 



		Integer (Number of elements)[N], Copy of n-integers.

- Error:



		Throw UnderFlow Error if stack is empty.



Example:



		5 10 15 // Push 5, 10, 15 to top of the stack. Stack contains [5, 10, 15]

		2 dupm  // Duplicate 10, 15. Stack now contains [5, 10, 15, 10, 15]

	



---



#### OP_OVER -> `over`







		Duplicate 1 element over current (»this«, current).

- Args:



		None.

- Input: 



		Copy of 1 element over current.

- Output: 



		Push that element to top of the stack.

- Error:



		Stack underflow if there are no 2 values.

Example:



		1 2  3  // On stack [1, 2, 3] 

		over // On stack [1, 2, 3, 2].



---



#### OP_OVERM -> `overm`







		Removes elements starting from the top of the stack going down as much as the user wants.

 		

- Args:



		None.

- Input: 



		Elements starting from the top of the stack.

- Output: 



		None.

- Error:



		Throw StackUnderflow Error if stack have less values, than over-index.

Example:



		1 2 3 4 5 

		3 overm

		// 1 2 3 4 5 2



---



#### OP_SWAP-> `swap`







		Swapping two values at the top of the stack.

- Args:



		None. 

- Input: 



		Takes two numbers.

- Output: 



		Returns two numbers in reverse order.

- Error:



		If there are not 2 values on the stack StackUnderflow.

Example:



		3 5 swap 

        5 3

---



#### OP_PLUS -> `+`







		At the end of the stack, it takes two elements and combines them into

		one and push back.

- Args:



		None.

- Input: 



		Takes 2 integers from top of the stack.

- Output: 



		Result of combine 2 elements.

- Error:



		Throw ValueError if values is not integers.

		Throw UnderflowError if stack size < 2.

Example:



		1 2 2 +

		// 1 4





---



#### OP_MINUS -> `-`







		Subtracts the first value from the second.

- Args:



		None.

- Input: 



		Two numbers.

- Output: 



		Answer after subtracting two numbers.

- Error:



		StackUnderflow if there are no 2 numbers.

Example:



		1 2 –

		// -1



---



#### OP_MUL -> `*`







	Multiplies the first value by the second.

- Args:



		None.

- Input: 



		Enters two values that it multiplies.

- Output: 



		Outputs the answer after multiplication.

- Error:



		StackUnderflow if there are no 2 numbers.

Example:



		5 10 *

		// 50



---



#### OP_DIV-> `//`







	Divides the first value by the second.

- Args:



		None.

- Input: 



		Enters two values that it divides.

- Output: 



		Outputs the answer after division.

- Error:



		StackUnderflow if there are no 2 numbers.

Example:



		10 5 //

		// 2





---



#### OP_MOD -> `%`







	Takes two numbers and returns the remainder of the division 1 by 2.

- Args:



		None.

- Input: 



		Takes two numbers.

- Output: 



		Returns the remainder.

- Error:



		StackUnderflow if there are no 2 numbers.

Example:



		4 2 %

        // 0

---



#### OP_DEBUG_INT -> `iDebug`







	Outputs the integer element of the top of the stack.

- Args:



		None.

- Input: 



		Takes an integer element of the top of the stack.

- Output: 



		Outputs the integer element from the top of the stack.

- Error:



		Throw StackUnderflow Error if stack is empty.

Example:



		1 2 3 iDebug



---



#### OP_DEBUG_CHAR -> `cDebug`







	We took a number and interpreted it as a character from the ASCII table.

- Args:



		None.

- Input: 



		Takes an integer value from the stack.

- Output: 



		We get the symbol by this value.

- Error:



		If the value is outside the table, the behavior is undefined.

		Stack Underflow error if the stack is empty.

Example:



		 104 cDebug

		//print “h” 



---



#### OP_MEM -> `mem`







	Return memory start pointer.

- Args:



		None.

- Input: 



		None.

- Output: 



		Pointer to a starting address in memory (to zero point).

- Error:



		No Errors.

Example:



		mem 		// 0x123456

		mem 3 + 	// 0x123459    



---



#### OP_MEM_PUSH-> `mPush`







	Takes a value from the stack and loads it into memory.

- Args:



		None.

- Input: 



		Takes a value from the stack and a point in memory.

- Output: 



		None.

- Error:



		StackUnderflow if there are not 2 values on the stack.

Example:



		mem 44 mPush

---



#### OP_MEM_LOAD -> `mLoad`







	Push to stack data from point of memory.

- Args:



		None.

- Input: 



		Pointer to memory.

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



		None.

- Input: 



		Name(Index) of syscall, syscall arguments, number of syscall 

		arguments + 1;

- Output: 



		None.

- Error:



		Throw Stack UnderFlowError if not enough values on stack

		Can throw  SEGFAULT if syscall changes memory. And do it wrong.

Example:



		        0 	 0 	    mem 		10 	         4 		syscall 

		//	(name)  (fd)	(pointer)	(size)	(number of args)	(call)





---



#### OP_EQUAL  -> `==`







	Takes two numbers from the stack and checks them for equality.

- Args:



		None.

- Input: 



		Takes two numbers.

- Output: 



		Returns 1 if the numbers are EQUAL 0 otherwise.

- Error:



		StackUnderflow if there are not 2 values on the stack.

Example:



		 2 4 == 

		// 0 (on stack)



---



#### OP_NOT_EQUAL-> `!=`







	Takes two values from the stack and compares them, returns 0 if equal

	otherwise 1.

- Args:



		None.

- Input: 



		Takes two integers.

- Output: 



		Returns 0 if the numbers are EQUAL 1 otherwise.

- Error:



		Throws Stack Underflow if there are no two values.

Example:



		4 4 

        //0



---



#### OP_GREATER-> ``>``







	Takes two values ​​and compares which value is greater.

- Args:



		None.

- Input: 



		Takes two values.

- Output: 



		Returns 1 if the first number is greater than the second.

- Error:



		StackUnderFlow If there are not 2 values on the stack.

Example:



		2 1 >

		//1

	

---



#### OP_LOWER -> `<`







	Takes two values and compares which value is lower.

- Args:



		None.

- Input: 

		Takes two values

		

- Output: 


		Returns 1 if the first number is lower than the second
		.

- Error:



		Throws Stack Underflow if there are no two values.

Example:



		1 2 <

		//1



---



#### OP_IF -> `if`



	Starts the if-block. Should be before condition. Marks condition start point.



- Args:

	

		None.

- Input: 

	

		None.

- Output: 

		

		None.

- Error:



		None.

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

	

		None.

- Input: 

	

		None.

- Output: 

		

		None.

- Error:



		Throw Error if no `if`-block.

Example:

	

		if 1 2 > :

		4 iDebug

		else :

		`5 iDebug

		end

	

		// Prints 5



---



#### OP_ELSE -> `else`



	Marks else-way in condition, can be used in if-block.



- Args:

	

		None.

- Input: 

	

		None.

- Output: 

		

		None.

- Error:



		Throw Error if no `if`-block.

Example:

	

		if 1 2 > :

		4 iDebug

		else :

		`5 iDebug

		end

	

	// Prints 5



---



#### OP_END-> `END`







	Completion of a special block (If, while) or some operation.

- Args:



		None.

- Input: 



		None.

- Output: 



		If there is no start of any block.

- Error:



		None.

Example:



		if 1:

	          1 2 3 4 5

		end



---



#### OP_WHILE -> `while`







	Starts the while-loop(block). Should be before condition. Marks condition start point.

- Args:



		None.

- Input: 



		None.

- Output: 



		None.

- Error:



		None.

Example:



		0 while dup 1 < :

	         1+

		end



---



#### OP_BITSHIFT_LEFT -> `<<`







	Bit shift left operation.

- Args:



		None.

- Input: 



		Takes two integers.

- Output: 



		The resulting number after the shift.

- Error:



		If he does not see two values, then there will be StackUnderFlow.

Example:



		2 1  << 4

        // 3

---



#### OP_BITSHIFT_RIGHT -> `>>`







	Bit shift to right operation.

- Args:



		None.

- Input: 



		Takes two integers.

- Output: 



		The resulting number after the shift.

- Error:



		If he does not see two values, then there will be StackUnderFlow.

Example:



		4 1 >> 2

        // 4



---



#### OP_AND_BIT-> `&`







	Returns the result of the AND bit operation between the first and second value.

- Args:



		None.

- Input: 



		Takes 2  values.

- Output: 



		Returns the result of bitwise and.

- Error:



		Throws Stack Underflow if there are no two values.

Example:



		1 2 

        //3



---



#### OP_OR_BIT  -> `|`







	Compares each bit of the first operand with the corresponding bit of the 

	second operand.

- Args:



		None.

- Input: 



		Takes two integers.

- Output: 



		Comparison result.

- Error:



		StackUnderFlor if there are not 2 values on the stack.

Example:



		3 2 |
        //1
        



---



#### OP_MACRO -> `macro`







	Prepares for execution a defined set operation by alias.

- Args:



		None.

- Input: 



		None.

- Output: 



		If there is no macro name, then it will not work.

- Error:



		if the macro name is missing, it will not work correctly.

Example:



		macro

		1 1 2 overm dup strlen 4 syscall endl

		drop

		macroEnd.





---



#### OP_MACRO_END -> `macroEnd`







	Indicates where the end of the macro is.

- Args:



		None.

- Input: 



		None.

- Output: 



		If there is no beginning of the macro, then there is nothing to end.

- Error:



		if there is no start of the macro.

Example:


		Macro 
		puts

		1 1 2 overm dup strlen 4 syscall endl 

		drop

		macroEnd

---



#### OP_MACRO_SET_NAME -> `set_name`







	Shows the beginning of the macro.

- Args:



		None.

- Input: 



		None.

- Output: 



		None.

- Error:



		there is no macro name.

Example:


		Macro 
		puts

		drop

		macroEnd

---



#### OP_MACRO_EXPAND -> `expand`







	calling a macro by its name.

- Args:



		accepts the macro name.

- Input: 



		depend on the contents of the macro.

- Output: 



		depend on the contents of the macro.

- Error:



		none.

Example:


		Macro 
		puts

		macroEnd

---




#### OP_INCLUDE -> `include`







	Includes in the program the file that is entered at the beginning.

- Args:



		None.

- Input: 



		Takes name of the file.

- Output: 



		Add code from imported file.

- Error:



		Gives an error if this file is not valid.

Example:



		"string.cims" include 



---
