javac com/craftinginterpreters/lox/*.java -d ./classes
java -cp classes com.craftinginterpreters.lox.Lox $1
