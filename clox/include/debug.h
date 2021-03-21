#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);
static int simpleInstruction(const char* name, int offset);
static int constantInstruction(const char* name, Chunk* chunk, int offset);

#endif
