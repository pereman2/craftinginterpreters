#include <stdlib.h>
#include <stdio.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initValueArray(&chunk->constants);
  initLineArray(&chunk->lineArray);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  printf("before\n");
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                             oldCapacity, chunk->capacity);

  }
  chunk->code[chunk->count] = byte;
  addLine(&chunk->lineArray, line);
  chunk->count++;
}

// lines -> 12 1 2 2
// first 12 are in line 1, next 2 are in line 2
// run length enconding
void addLine(LineArray* lineArray, int line) {
  printf("line %d count %d\n", line, lineArray->count);
  if (line == lastLineValue(lineArray)) {
    incrementLastLine(lineArray);
    return;
  }
  printf("line %d count %d capacity %d\n", line, lineArray->count, lineArray->capacity);
  if(lineArray->capacity < lineArray->count + 2) {
    int oldCapacity = lineArray->capacity;
    lineArray->capacity = GROW_CAPACITY(oldCapacity);
    lineArray->lines = GROW_ARRAY(int, lineArray->lines,
                             oldCapacity, lineArray->capacity);
  }
  printf("line %d count %d capacity %d\n", line, lineArray->count, lineArray->capacity);
  printf("bro\n");
  lineArray->lines[lineArray->count] = 1;
  printf("line %d count %d\n", line, lineArray->count);
  lineArray->lines[lineArray->count + 1] = line;
  lineArray->count += 2;
}

void incrementLastLine(LineArray* lineArray) {
  if (lineArray->count < 2) {
    printf("Cannot increment last line value");
    exit(0);
  }
  lineArray->lines[lineArray->count - 2]++;
}

int lastLineValue(LineArray* lineArray) {
  if (lineArray->count < 2) {
	  return -1;
  }
  return lineArray->lines[lineArray->count - 1];
}

int getLine(LineArray* lineArray, int index) {
  int count = 0;
  for (int i = 0; i < lineArray->count; i += 2) {
    count += lineArray->lines[i];
    if (index < count) {
      return lineArray->lines[i+1];
    }
  }
  printf("Index out of bounds");
  exit(0);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  freeLineArray(&chunk->lineArray);
  initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void initLineArray(LineArray* lineArray) {
  lineArray->capacity = 0;
  lineArray->count = 0;
  lineArray->lines = NULL;
}

void freeLineArray(LineArray* lineArray) {
  FREE_ARRAY(int, lineArray->lines, lineArray->capacity);
  initLineArray(lineArray);
}

