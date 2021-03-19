# craftinginterpreters book


This repo is just me following craftinginterpreter's book and reproducing it. 


## Grammar

```
program        → declaration* EOF;

declaration    → funDecl
                | varDecl
                | statement
statement      → exprStmt
                | ifStmt
                | forStmt
                | returnStmt
                | whileStmt
                | breakStmt
                | printStmt
                | block
                
breakStmt      → "break" ";";
forStmt        → "for" "(" ( varDecl | exprStmt | ";" )
                expression? ";"
                expression? ")" statement ;

returnStmt     → "return" expression? ";" ;
whileStmt      → "while" "(" expression ")" statement ;
ifStmt         → "if" "(" expression  ")" statement ("else" statement )? ;

block          → "{" declaration* "}" ;
                
funDecl        → "fun" function ;
function       → IDENTIFIER "(" parameters? ")" block ;
varDecl        → "var" IDENTIFIER ( "=" expression )? ";" ;
parameters     → IDENTIFIER ( "," IDENTIFIER )* ;

                
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
unary          → ( "!" | "-" ) unary | call ;
call           → primary ( "(" arguments? ")" )* ;
arguments      → expression ( "," expression )* ;
primary        → "true" | "false" | "nil"
                | NUMBER | STRING
                | "(" expression ")"
                | IDENTIFIER ;
```
