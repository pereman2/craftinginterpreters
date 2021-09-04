#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_RETURN,
  OP_CONSTANT,
  OP_NEGATE,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
} OpCode;

typedef struct {
  int capacity;
  int count;
  int *lines;
} LineArray;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  LineArray lineArray;
  ValueArray constants;
} Chunk;


void initChunk(Chunk* cunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);
void printValue(Value value);
int getLine(LineArray* lineArray, int line);
void initLineArray(LineArray* lineArray);
void freeLineArray(LineArray* lineArray);
void addLine(LineArray* lineArray, int line);
void incrementLastLine(LineArray* lineArray);
int lastLineValue(LineArray* lineArray);

#endif

