#include "ast.h"
#include <stdlib.h>
#include <string.h>

ASTNode *create_int_literal(int value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_INT_LITERAL;
  node->as.int_lit.value = value;
  return node;
}

ASTNode *create_return(ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_RETURN;
  node->as.return_stmt.value = value;
  return node;
}

ASTNode *create_block(ASTNode **statements, int count) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_BLOCK;
  node->as.block.statements = statements;
  node->as.block.count = count;
  return node;
}

ASTNode *create_type(const char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_TYPE;
  node->as.type.name = strdup(name);
  return node;
}

ASTNode *create_function(const char *name, ASTNode *return_type,
                         ASTNode *body) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_FUNCTION;
  node->as.function.name = strdup(name);
  node->as.function.return_type = return_type;
  node->as.function.body = body;
  return node;
}

ASTNode *create_program(ASTNode **functions, int count) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_PROGRAM;
  node->as.program.functions = functions;
  node->as.program.count = count;
  return node;
}
