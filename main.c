#include "include/ast.h"
#include "include/codegen.h"
#include "include/parser.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Token tokens[12] = {{TOKEN_KEYWORD_FUNC, {0}},
                      {TOKEN_IDENTIFIER, {.identifier = "main"}},
                      {TOKEN_OPEN_PAREN, {0}},
                      {TOKEN_CLOSE_PAREN, {0}},
                      {TOKEN_ARROW, {0}},
                      {TOKEN_KEYWORD_INT, {0}},
                      {TOKEN_OPEN_BRACE, {0}},
                      {TOKEN_KEYWORD_RETURN, {0}},
                      {TOKEN_INTEGER_LITERAL, {.int_value = 0}},
                      {TOKEN_SEMICOLON, {0}},
                      {TOKEN_CLOSE_BRACE, {0}},
                      {TOKEN_EOF, {0}}};

  Parser parser;
  parser.tokens = tokens;
  parser.position = 0;
  parser.length = 12;

  int function_count = 0;
  ASTNode **functions = malloc(sizeof(ASTNode *) * 10);

  while (parser.tokens[parser.position].type != TOKEN_EOF) {
    Token current = parser.tokens[parser.position];

    if (current.type == TOKEN_KEYWORD_FUNC) {
      ASTNode *function_node = parse_function(&parser);
      functions[function_count] = function_node;
      function_count++;
    }
  }

  ASTNode *program = create_program(functions, function_count);

  generate_assembly(program, "output.s");

  return 0;
}
