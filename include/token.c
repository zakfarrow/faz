#include "token.h"
#include <string.h>

void tokenizer_init(Tokenizer *t, const char *source) {
  t->source = source;
  t->position = 0;
  t->length = strlen(source);
}

char tokenizer_peek(Tokenizer *t) {
  if (t->position >= t->length)
    return '\0';
  return t->source[t->position];
}

char tokenizer_advance(Tokenizer *t) {
  if (t->position >= t->length)
    return '\0';
  return t->source[t->position++];
}
