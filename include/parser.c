#include "parser.h"
#include "ast.h"
#include <stdlib.h>

ASTNode *parse_return_statement(Parser *parser) {
  parser->position++;

  int value = parser->tokens[parser->position].value.int_value;
  ASTNode *literal = create_int_literal(value);
  parser->position++;

  parser->position++;

  return create_return(literal);
}

ASTNode *parse_block(Parser *parser) {
  ASTNode **statements = malloc(sizeof(ASTNode *) * 10);
  int count = 0;

  while (parser->tokens[parser->position].type != TOKEN_CLOSE_BRACE) {
    if (parser->tokens[parser->position].type == TOKEN_KEYWORD_RETURN) {
      statements[count] = parse_return_statement(parser);
      count++;
    }
  }

  parser->position++;

  return create_block(statements, count);
}

ASTNode *parse_function(Parser *parser) {
  parser->position++;

  char *func_identifier = parser->tokens[parser->position].value.identifier;
  parser->position++;

  parser->position++;

  parser->position++;

  parser->position++;

  ASTNode *return_type = create_type("int");
  parser->position++;

  parser->position++;

  ASTNode *body = parse_block(parser);

  return create_function(func_identifier, return_type, body);
}
