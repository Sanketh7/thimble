#include "draw.h"

int gnid;
FILE* f;

static void draw(Node* node, int nid);
static void draw_binop(Node *node, int nid);
static void draw_unop(Node *node, int nid);
static void draw_intconst(Node *node, int nid);
static void draw_var(Node *node, int nid);
static void draw_statementlist(Node *node, int nid);
static void draw_vardecl(Node* node, int nid);
static void draw_varassign(Node* node, int nid);
static void emit_node(int nid, char* label);
static void emit_edges(int par, int child[], int size);
static const char* op_to_string(Op op);
static const char* datatype_to_string(DataType datatype);

void emit_dot(Node* node) {
    gnid = 1;
    f = fopen("ast.dot", "w");
    fprintf(f, "graph G {\n");
    draw(node, gnid);
    fprintf(f, "}\n");
}

static void draw(Node* node, int nid) {
    switch (node->nodeType) {
        case NT_BinOp: draw_binop(node, nid); break;
        case NT_UnOp: draw_unop(node, nid); break;
        case NT_IntConst: draw_intconst(node, nid); break;
        case NT_Var: draw_var(node, nid); break;
        case NT_StatementList: draw_statementlist(node, nid); break;
        case NT_VarDecl: draw_vardecl(node, nid); break;
        case NT_VarAssign: draw_varassign(node, nid); break;
        default: fprintf(stderr, "Unknown node type."); exit(1);
    }
}

static void draw_binop(Node *node, int nid) {
    assert(node->nodeType == NT_BinOp);
    int child[2] = {++gnid, ++gnid};

    emit_node(nid, op_to_string(node->BinOp.op));
    emit_edges(nid, child, 2);

    draw(node->BinOp.left, child[0]);
    draw(node->BinOp.right, child[1]);
} 

static void draw_unop(Node *node, int nid) {
    assert(node->nodeType == NT_UnOp);
    int child[1] = {++gnid};

    emit_node(nid, op_to_string(node->UnOp.op));
    emit_edges(nid, child, 1);

    draw(node->UnOp.expr, child[1]);
}

static void draw_intconst(Node *node, int nid) {
    assert(node->nodeType == NT_IntConst);
    char numstr[50]; // TODO: maybe make this based on actual length
    sprintf(numstr, "%d", node->IntConst.ival);
    emit_node(nid, numstr);
}

static void draw_var(Node *node, int nid) {
    assert(node->nodeType == NT_Var);
    emit_node(nid, node->Var.id);
}

static void draw_statementlist(Node *node, int nid) {
    assert(node->nodeType == NT_StatementList);
    int len = node->StatementList.children->size;
    int child[len];
    for (int i = 0; i < len; i++) {
        child[i] = gnid+i+1;
    }
    gnid += len+1;

    emit_node(nid, "Statement List");
    emit_edges(nid, child, len);

    for (int i = 0; i < len; i++) {
        draw(vector_get(node->StatementList.children, i), child[i]);
    }
}

static void draw_vardecl(Node* node, int nid) {
    assert(node->nodeType == NT_VarDecl);
    int child[2] = {++gnid, ++gnid};

    emit_node(nid, "let");
    emit_edges(nid, child, 2);

    draw(node->VarDecl.var, child[0]);
    emit_node(child[1], datatype_to_string(node->VarDecl.dataType));
}

static void draw_varassign(Node* node, int nid) {
    assert(node->nodeType == NT_VarAssign);
    int child[2] = {++gnid, ++gnid};
    
    emit_node(nid, "=");
    emit_edges(nid, child, 2);

    draw(node->VarAssign.var, child[0]);
    draw(node->VarAssign.expr, child[1]);
}







static void emit_node(int nid, char* label) {
    fprintf(f, "%d [label = \"%s\"]\n", nid, label);
}

static void emit_edges(int par, int child[], int size) {
    fprintf(f, "%d -- {", par);
    for (int i = 0; i < size; i++) {
        fprintf(f, "%d ", child[i]);
    }
    fprintf(f, "}\n");
}

static const char* op_to_string(Op op) {
    switch (op) {
        case O_ADD: return "+";
        case O_SUB: return "-";
        case O_MULT: return "*";
        case O_DIV: return "/";
        default: return "";
    }
}

static const char* datatype_to_string(DataType datatype) {
    switch (datatype) {
        case DT_VOID: return "void";
        case DT_INT: return "int";
        default: return "";
    }
}