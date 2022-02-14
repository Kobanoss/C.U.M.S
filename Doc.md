# DOCUMENTATION FOR C.U.M.S.


## BASE OPERATIONS LIST

#### OP_PUSH_INT (push)

	Adding integer value to top of the stack.
- Args:
	
		Integer
- Input: 
	
		None
- Output: 
	
		None
- Error:

		None
Example:
	
	push 5


---
#### OP_DROP (drop) 

	Removing integer value from top of the stack.
		
- Args:
	
		None
- Input: 
	
		None
- Output: 
	
		None

- Error:

		Throw UnderFlowError if drop called in empty stack.
Example:
	
	push 5
	drop 
---


	  
