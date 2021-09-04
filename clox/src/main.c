#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  printf("init chunk\n");
  initChunk(&chunk);
  printf("add chunk\n");
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_NEGATE, 123);
  writeChunk(&chunk, OP_ADD, 123);
  constant = addConstant(&chunk, 4);
  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, constant, 124);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, constant, 124);
  writeChunk(&chunk, OP_DIVIDE, 124);
  writeChunk(&chunk, OP_MULTIPLY, 124);

  writeChunk(&chunk, OP_RETURN, 125);

  printf("disa\n");
  disassembleChunk(&chunk, "test chunk");
  printf("interpret\n");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}

