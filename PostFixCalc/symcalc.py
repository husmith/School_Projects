"""
Symbolic calculator - 
   Reads input in postfix format from standard input
   Normally builds expression tree; # means evaluate the top item
   
   Authors: Hannah Smith
   Consulted with: Kirsten Dawes
   
"""

import argparse  # Command line parsing
import numbers   # To get numbers.Number, for testing types
import re        ## Regular expression pattern matching, for user input
import sys      # For reading from sys.stdin (keyboard or redirected file)

##### 
# Calculator arithmetic operations
#
# We could define our own functions for addition, subtraction, etc., 
# but Python has helpfully done that for us already in the module "operator". 
# We can store these functions in a dictionary, associated with the symbols
# that the user enters in the calculator. 
####
import operator ### Standard Python operations, as named functions
    
# OPS is used both in parsing input, and in the expression evaluator
OPS = { "+": operator.add, "-": operator.sub,
        "*" : operator.mul, "/" : operator.truediv }



####
#  This calculator can work with integers and floating point numbers, 
#  and with symbols (variable names) that are just treated as strings 
#  and cannot be evaluated.  In evaluation, we need to know whether 
#  the thing we are looking at is a number that we can do arithmetic on. 
#
def is_number(x):
    """Determine if x is a number (float, int, etc)
       
        Arguments: 
            x: a value that might or might not be a number
        Returns: 
            True iff type type of x is one of Python's numeric types
    """
    return isinstance(x,numbers.Number)

#  Similarly, we need to know whether we are working on a leaf node
#  (which could be a number or a string) or a more complex expression.
#  Anything that is not a list must be a leaf node in the tree. 
#
def is_leaf(x):
    """Determine if x is a leaf node (as versus a list representing
    a more complex expression).
    Arguments:
        x:  An expression, which might be a leaf or an interior node.
    Returns:
        True iff the type of x is not a list.
    """
    return not isinstance(x,list)


######

def expstr(e):
    """Pretty-print an expression in full parenthesized 
       infix notation. 
       Arguments: 
           e:  An expression, either a leaf of [operation operand operand]
       Returns: 
           A string representation of e in infix form, fully
           parenthesized. 
        Example: 
            expstr([+ 7 [- 3 "x"]]) => "(7+(3-x))"
    """
    if is_leaf(e):
        return str(e)
    if isinstance(e, list):
        for elem in e: 
            if elem in OPS:
                op = elem
                right = e[2]
                left = e[1]
                st = "("+expstr(left)+op+expstr(right)+")"
                return st
    return e
    
def evaluate(e):
    """Evaluate expression as far as possible.  Any arithmetic 
       operation whose operands can be evaluated to a number is 
       evaluated. 
       Arguments: 
           e:  An expression in nested list form (S-expression).
        Returns: 
           An expression also in nested list form, but with all 
           sub-expressions evaluated as far as possible. 
        Examples: 
           17 => 17
           [+ 16 5] => 21
           [+ x 5] => [+ x 5]
           [+ [+ x 5] [+ 16 5]] => [+ [+ x 5] 21]
    """   
    if is_leaf(e):
        return e
    else:
        if e[0] in OPS:
            right = e[2]
            left = e[1]
            left = evaluate(left)
            right = evaluate(right)
            if is_number(left) and is_number(right):
                st = OPS[e[0]](left,right)
                return st
            else:
                return [e[0], left, right]
        return e                
        

def interpret(inp):
    """Read and interpret each line of input.
    Args:
       inp:  The input file (which might be the keyboard)
    Returns:
       nothing
    Effects:
       Interactive loop - displays calculator stack after
       each line of input.  Exits when the "quit" token is
       encountered, or at end of file.
    """



    FLOATPAT = re.compile(r"""\-?\d+\.\d*$""")  ### Float number, e.g., 42.9
    INTPAT = re.compile(r"""\-?\d+$""")         ### Integer with optional sign
    VARPAT = re.compile(r"""[a-zA-Z]+[a-zA-Z0-9_]*$""") ### Variable names 

    stack = [ ] ## Calculator stack
    for line in inp:
        try:
            for token in line.strip().split():

                if token == "#" : 
                    ### Recursively evaluate an expression, from 
                    ### symbolic form to a number if possible
                    stack.append(evaluate(stack.pop()))

                elif token == "cl" : 
                    ### Clear the stack
                    stack = [ ] 

                elif token == "^" : 
                    ### Clear one item from the stack
                    stack.pop()

                elif token == "quit":
                    print("Thank you for your patience.  Sorry for any bugs.")
                    exit(0)

                elif token in OPS:
                    ### An arithmetic expression - keep it symbolic for now
                    right = stack.pop()
                    left = stack.pop()
                    stack.append([ token, left, right ])

                elif re.match(INTPAT,token):
                    ### Looks like an integer (digits only)
                    stack.append(int(token))

                elif re.match(FLOATPAT,token): 
                    ### Looks like a floating point number
                    stack.append(float(token))

                elif re.match(VARPAT,token):
                    stack.append(token)

                else: 
                    ### Anything else?  
                    print("Unknown token '" + token + "', skipping it")

            print("Stack: ", end="")
            for expr in stack: 
                print(expstr(expr), end="; ")
            print()
        except IndexError as e: 
            print("Expression syntax: Too many operations for available operands")
        except Exception as e: 
            print("Unexpected exception: ", type(e))
            print(e)


def main(): 
    ###
    # Command line may hold input file name, or -- to indicate stdin
    ###

   parser = argparse.ArgumentParser(description="""
   Read and print arithmetic expressions, with optional 
   evaluation.""",
   epilog="""
   Input (file or keyboard) is in postfix (reverse Polish notation), with each
   operation or operand separated by whitespace.  Integers and floating point
   numbers are interpreted as numbers.  Recognized operators are:
   #    (evaluate top item on stack)
   cl   (clear the stack)
   ^    (remove top item from stack)
   quit (quit)
   +    (addition)
   -    (subtraction)
   *    (multiplication)
   /    (division)
   Anything else is interpreted as a variable name.
   Example:   5 3 + x * is interpreted as (5+3)*x,
   and 5 3 + x * # evaluates to 8*x
   """,
   formatter_class=argparse.RawDescriptionHelpFormatter
   )

   parser.add_argument('input', metavar="filename",
                    nargs = '?', ### It's optional
                    type=argparse.FileType('r'), 
                    default=sys.stdin, 
                    help="input source (file name or - for command line)")

   args = parser.parse_args()

   interpret(args.input)

if __name__ == "__main__":
    main()
    
