#include "include/ast.h"
#include "include/codegen.h"
#include "include/parser.h"
#include "include/token.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  // Test tokens:
  // Token tokens[12] = {{TOKEN_KEYWORD_FUNC, {0}},
  //                     {TOKEN_IDENTIFIER, {.identifier = "main"}},
  //                     {TOKEN_OPEN_PAREN, {0}},
  //                     {TOKEN_CLOSE_PAREN, {0}},
  //                     {TOKEN_ARROW, {0}},
  //                     {TOKEN_KEYWORD_INT, {0}},
  //                     {TOKEN_OPEN_BRACE, {0}},
  //                     {TOKEN_KEYWORD_RETURN, {0}},
  //                     {TOKEN_INTEGER_LITERAL, {.int_value = 0}},
  //                     {TOKEN_SEMICOLON, {0}},
  //                     {TOKEN_CLOSE_BRACE, {0}},
  //                     {TOKEN_EOF, {0}}};

  Token tokens[12];

  tokens[0].type = TOKEN_KEYWORD_FUNC;

  if (argc != 2) {
    printf("Error: you must supply an input (.faz) file argument.\n");
    printf("Example usage: faz main.faz\n");
    return 1;
  }

  FILE *input_file = fopen(argv[1], "r");
  if (!input_file) {
    fprintf(stderr, "Error: Could not open file '%s'\n", argv[1]);
    return 1;
  }

  int ch;
  char token[256];
  int token_length = 0;
  int token_count = 0;

  while ((ch = fgetc(input_file)) != EOF) {
    if (isalnum(ch) || ch == '_') {
      token[token_length++] = ch;
    } else {
      if (token_length > 0) {
        token[token_length] = '\0';
        if (strcmp(token, "func") == 0) {
          tokens[token_count].type = TOKEN_KEYWORD_FUNC;
          token_count++;
        } else if (strcmp(token, "return") == 0) {
          tokens[token_count].type = TOKEN_KEYWORD_RETURN;
          token_count++;
        } else if (strcmp(token, "int") == 0) {
          tokens[token_count].type = TOKEN_KEYWORD_INT;
          token_count++;
        } else if (isdigit(token[0])) {
          char *endptr;
          errno = 0;
          long value = strtol(token, &endptr, 10);

          if (errno == 0 && *endptr == '\0' && value >= INT_MIN &&
              value <= INT_MAX) {
            tokens[token_count].type = TOKEN_INTEGER_LITERAL;
            tokens[token_count].value.int_value = value;
            token_count++;
          } else {
            return 1;
          }
        } else {
          tokens[token_count].type = TOKEN_IDENTIFIER;
          tokens[token_count].value.identifier = strdup(token);
          token_count++;
        }

        token_length = 0;
      }

      if (ch == ';') {
        tokens[token_count].type = TOKEN_SEMICOLON;
        token_count++;
      } else if (ch == '(') {
        tokens[token_count].type = TOKEN_OPEN_PAREN;
        token_count++;
      } else if (ch == ')') {
        tokens[token_count].type = TOKEN_CLOSE_PAREN;
        token_count++;
      } else if (ch == '{') {
        tokens[token_count].type = TOKEN_OPEN_BRACE;
        token_count++;
      } else if (ch == '}') {
        tokens[token_count].type = TOKEN_CLOSE_BRACE;
        token_count++;
      } else if (ch == '-') {
        int next_ch = fgetc(input_file);
        if (next_ch == '>') {
          tokens[token_count].type = TOKEN_ARROW;
          token_count++;
        } else {
          ungetc(next_ch, input_file);
        }
      } else if (!isspace(ch)) {
        printf("Unknown token: %c\n", ch);
        return 1;
      }
    }
  }

  tokens[token_count].type = TOKEN_EOF;

  fclose(input_file);

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

  // Free memory
  for (int i = 0; i < token_count; i++) {
    if (tokens[i].type == TOKEN_IDENTIFIER) {
      free(tokens[i].value.identifier);
    }
  }

  return 0;
}
