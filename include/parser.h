#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
#include "token.h"
#include <stdio.h>

typedef struct {
  Token *tokens;
  int position;
  int length;
} Parser;

ASTNode *parse_block(Parser *parser);

ASTNode *parse_function(Parser *parser);

ASTNode *parse_return_statement(Parser *parser);

#endif
