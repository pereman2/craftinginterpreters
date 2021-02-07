# craftinginterpreters book


This repo is just me following craftinginterpreter's book and reproducing it. 


## Grammar

```
comma_series   → expression ( "," expression )* ;
expression     → ternary ;
ternary        → equality ( "?" ternary_right )* ;
ternary_right  → equality ":" equality;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
                | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
                | "(" expression ")" ;
```
