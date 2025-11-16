#ifndef AST_H
#define AST_H

typedef enum {
  NODE_PROGRAM,
  NODE_FUNCTION,
  NODE_BLOCK,
  NODE_RETURN,
  NODE_INT_LITERAL,
  NODE_TYPE
} NodeType;

typedef struct ASTNode ASTNode;

struct ASTNode {
  NodeType type;
  union {
    struct {
      ASTNode **functions;
      int count;
    } program;

    struct {
      char *name;
      ASTNode *return_type;
      ASTNode *body;
    } function;

    struct {
      ASTNode **statements;
      int count;
    } block;

    struct {
      ASTNode *value;
    } return_stmt;

    struct {
      int value;
    } int_lit;

    struct {
      char *name;
    } type;
  } as;
};

ASTNode *create_int_literal(int value);

ASTNode *create_return(ASTNode *value);

ASTNode *create_block(ASTNode **statements, int count);

ASTNode *create_type(const char *name);

ASTNode *create_function(const char *name, ASTNode *return_type, ASTNode *body);

ASTNode *create_program(ASTNode **functions, int count);

#endif
