#include "vm.h"

#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "memory.h"

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }
void initVM() {
  vm.count = 0;
  vm.capacity = GROW_CAPACITY(0);
  vm.stack = GROW_ARRAY(Value, vm.stack,
                           0, vm.capacity);
  resetStack();
}

void freeVM() {}

void push(Value value) {
  if(vm.capacity < vm.count + 1) {
    int oldCapacity = vm.capacity;
    vm.capacity = GROW_CAPACITY(oldCapacity);
    vm.stack = GROW_ARRAY(Value, vm.stack,
                             oldCapacity, vm.capacity);
  }
  *vm.stackTop = value;
  vm.stackTop++;
  vm.count++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a op b); \
    } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_printf("          ");
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        printValue(constant);
        printf("\n");
        break;
      }

      case OP_NEGATE: {
        *(vm.stackTop-1) = -(*(vm.stackTop - 1));
        Value negated = *(vm.stackTop-1);
        printValue(negated);
        printf("\n");
        break;
      }
      case OP_ADD:
        BINARY_OP(+);
        break;
      case OP_SUBTRACT:
        BINARY_OP(-);
        break;
      case OP_MULTIPLY:
        BINARY_OP(*);
        break;
      case OP_DIVIDE:
        BINARY_OP(/);
        break;

      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

