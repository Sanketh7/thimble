#ifndef AST_H_
#define AST_H_

#include <stdlib.h>
#include <assert.h>
#include "vector.h"

typedef enum {
    NT_BinOp,
    NT_UnOp,
    NT_IntConst,
    NT_Var,

    NT_StatementList,
    NT_VarDecl,
    NT_VarAssign
} NodeType;

typedef enum {
    DT_VOID,
    DT_INT,
} DataType;

typedef enum {
    O_ADD,
    O_SUB,
    O_MULT,
    O_DIV
} Op;

typedef struct Node {
    NodeType nodeType;

    union {
        // BinOp
        struct {
            struct Node* left;
            struct Node* right;
            Op op;
        } BinOp;

        // UnOp
        struct {
            struct Node* expr;
            Op op;
        } UnOp;

        // IntConst
        struct {
            int ival;
        } IntConst;

        // Var
        struct {
            char* id;
        } Var;
        
        // StatementList
        struct {
            Vector* children;
        } StatementList;

        // VarDecl
        struct {
            struct Node* var;
            DataType dataType;
        } VarDecl;

        // VarAssign
        struct {
            struct Node* var;
            struct Node* expr;
        } VarAssign;
    };
} Node;

Node* make_binop(Node* _left, Node* _right, Op _op);
Node* make_unop(Node* _expr, Op _op);
Node* make_intconst(int _ival);
Node* make_var(char* _id);

Node* make_statementlist();
void statementlist_addchild(Node* node, Node* child);
Node* make_vardecl(Node* _var, DataType _dataType);
Node* make_varassign(Node* _var, Node* _expr);

#endif