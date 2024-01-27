# Infix to Postfix Expression Evaluator

This C program converts an infix mathematical expression to its equivalent postfix form and then evaluates the result. The program utilizes two custom stacks for characters and floats, providing a comprehensive implementation of the Shunting Yard Algorithm.


## Features
- Converts infix expressions to postfix.
- Evaluates postfix expressions.
- Supports basic arithmetic operations: +, -, *, /, ^.
- Handles parentheses for correct expression evaluation.
- Provides clear error messages for unbalanced parentheses and invalid input.

## Prerequisites
- C Compiler (e.g., GCC)
- Standard C Libraries

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/infix-to-postfix-evaluator.git
   cd infix-to-postfix-evaluator

##Usage
1.Run the program `./Source.cpp`
2.Put an Infix Expressiion

##Example
Type your infix expression: (3 + 5) * 2
Converted to postfix: 3 5 + 2 *
Result: 16.00
