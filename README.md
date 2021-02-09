# craftinginterpreters book


This repo is just me following craftinginterpreter's book and reproducing it. 


## Grammar

```
program        → declaration* EOF;

declaration    → varDecl
                | statement
statement      → exprStmt
                | ifStmt
                | forStmt
                | whileStmt
                | breakStmt
                | printStmt
                | block
                
breakStmt      → "break" ";";
forStmt        → "for" "(" ( varDecl | exprStmt | ";" )
                expression? ";"
                expression? ")" statement ;
whileStmt      → "while" "(" expression ")" statement ;
ifStmt         → "if" "(" expression  ")" statement ("else" statement )? ;

block          → "{" declaration* "}" ;
                
varDecl        → "var" IDENTIFIER ( "=" expression )? ";" ;
                
exprtStmt      → expression ";";
printStmt      → "print" expression ";";


expression     → comma_series ;
comma_series   → assignment ( "," assignment )* ;
assignment     → IDENTIFIER "=" assignment
               | ternary ;
ternary        → logic_or ( "?" ternary_right )* ;
                | logic_or
ternary_right  → equality ":" equality;
logic_or       → logic_and ( "or" logic_and )* ;
logic_and      → equality ( "and" equality )* ;

equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
                | primary ;
primary        → "true" | "false" | "nil"
                | NUMBER | STRING
                | "(" expression ")"
                | IDENTIFIER ;
```
