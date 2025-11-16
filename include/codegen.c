#include "codegen.h"
#include <stdio.h>

static void generate_program(ASTNode *node, FILE *output);
static void generate_function(ASTNode *node, FILE *output);
static void generate_block(ASTNode *node, FILE *output);
static void generate_statement(ASTNode *node, FILE *output);
static void generate_return(ASTNode *node, FILE *output);
static void generate_expression(ASTNode *node, FILE *output);

void generate_assembly(ASTNode *program, const char *output_filename) {
  FILE *output = fopen(output_filename, "w");
  if (!output) {
    printf("Error: Could not open output file\n");
    return;
  }

  generate_program(program, output);

  fclose(output);
  printf("Assembly written to %s\n", output_filename);
}

static void generate_program(ASTNode *node, FILE *output) {

  fprintf(output, ".intel_syntax noprefix\n\n");
  for (int i = 0; i < node->as.program.count; i++) {
    generate_function(node->as.program.functions[i], output);
  }
}

static void generate_function(ASTNode *node, FILE *output) {
  char *func_name = node->as.function.name;

  fprintf(output, ".global %s\n", func_name);
  fprintf(output, "%s:\n", func_name);

  generate_block(node->as.function.body, output);
}

static void generate_block(ASTNode *node, FILE *output) {
  for (int i = 0; i < node->as.block.count; i++) {
    generate_statement(node->as.block.statements[i], output);
  }
}

static void generate_statement(ASTNode *node, FILE *output) {
  switch (node->type) {
  case NODE_RETURN:
    generate_return(node, output);
    break;
  default:
    printf("Unknown statement type\n");
    break;
  }
}

static void generate_return(ASTNode *node, FILE *output) {
  generate_expression(node->as.return_stmt.value, output);

  fprintf(output, "    ret\n");
}

static void generate_expression(ASTNode *node, FILE *output) {
  switch (node->type) {
  case NODE_INT_LITERAL:
    fprintf(output, "    mov rax, %d\n", node->as.int_lit.value);
    break;
  default:
    printf("Unknown expression type\n");
    break;
  }
}
