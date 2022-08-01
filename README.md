# Big Number Calculator
Simple calculator program that can handle big numbers, using C. (Programming class assignment, June 2018)

## How to run
1. Compile calculator.c
2. Enter a sequence of a mathematical expression, made up of integers and +, -, *, /
3. Enter 'stop' to stop.

## Program Structure
- The input expression is decomposed into an array of numbers and an array of operators.
- Each number is a struct which contains the sign and the string itself.

- Each operation is done very similarly to how we would do it in hand, using carry and borrow.

Program structure is explained in more detail at `Document.docx` and `Presentation.pptx`.

## Execution Example
![image](https://user-images.githubusercontent.com/11360981/182261241-14cd443f-44fe-4f50-90ee-163046ee2c41.png)
