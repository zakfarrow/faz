#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <stdio.h>

void generate_assembly(ASTNode *program, const char *output_filename);

#endif
