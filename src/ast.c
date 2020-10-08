#include "ast.h"

Node* make_binop(Node* _left, Node* _right, Op _op) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_BinOp;
    node->BinOp.left = _left;
    node->BinOp.right = _right;
    node->BinOp.op = _op;
    return node;
}

Node* make_unop(Node* _expr, Op _op) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_UnOp;
    node->UnOp.expr = _expr;
    node->UnOp.op = _op;
    return node;
}

Node* make_intconst(int _ival) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_IntConst;
    node->IntConst.ival = _ival;
    return node;
}

Node* make_var(char* _id) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_Var;
    node->Var.id = _id;
    return node;
}

Node* make_statementlist() {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_StatementList;
    node->StatementList.children = make_vector();
    return node;
}

void statementlist_addchild(Node* node, Node* child) {
    assert(node->nodeType == NT_StatementList);
    vector_pushback(node->StatementList.children, child);
}

Node* make_vardecl(Node* _var, DataType _dataType) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_VarDecl;
    node->VarDecl.var = _var;
    node->VarDecl.dataType = _dataType;
    return node;
}

Node* make_varassign(Node* _var, Node* _expr) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->nodeType = NT_VarAssign;
    node->VarAssign.var = _var;
    node->VarAssign.expr = _expr;
    return node;
}