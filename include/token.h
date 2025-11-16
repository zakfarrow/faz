#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  TOKEN_KEYWORD_FUNC,
  TOKEN_IDENTIFIER,
  TOKEN_OPEN_PAREN,
  TOKEN_CLOSE_PAREN,
  TOKEN_ARROW,
  TOKEN_KEYWORD_INT,
  TOKEN_OPEN_BRACE,
  TOKEN_KEYWORD_RETURN,
  TOKEN_INTEGER_LITERAL,
  TOKEN_SEMICOLON,
  TOKEN_CLOSE_BRACE,
  TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  union {
    char *identifier;
    int int_value;
  } value;
} Token;

#endif
