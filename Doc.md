# DOCUMENTATION FOR C.U.M.S.


## BASE OPERATIONS LIST

#### OP_PUSH_INT (`push`)

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
	
	push 5 // Add 5 to top of the stack


---
#### OP_DROP (`drop`) 

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
	
	push 5 	// Add 5 to top of the stack
	drop 	// Remove 5 from top of the stack
---


	  
