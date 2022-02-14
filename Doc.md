# DOCUMENTATION FOR C.U.M.S.


## BASE OPERATIONS LIST

#### `OP_PUSH_INT` :: `push`

	Add integer value to top of the stack.
- Args:
	
		Integer
- Input: 
	
		None
- Output: 
		
		New element on top of the stack.
- Error:

		Throw TypeError if value is not integer.
Example:
	
	// Add 5 to top of the stack
	push 5 


---
#### `OP_DROP` :: `drop`

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
	
	// Add 5 to top of the stack
	push 5 	
	// Remove 5 from top of the stack
	drop 	
---


	  
