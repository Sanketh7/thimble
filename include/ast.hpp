#pragma once

#include <vector>
#include <string>
#include <memory>

#include "operator.hpp"
#include "datatype.hpp"

namespace thimble {
  class Node {};

  /* EXPRESSIONS */
  class Expression : public Node {};

  class BinOp : public Expression {
  public:
    std::unique_ptr<Expression> left;
    Operator op;
    std::unique_ptr<Expression> right;
    BinOp(std::unique_ptr<Expression> &left, Operator op, std::unique_ptr<Expression> &right) 
      : left(std::move(left)), op(op), right(std::move(right)) {} // note that std::move() moves ownership
  };

  class UnOp : public Expression {
  public:
    Operator op;
    std::unique_ptr<Expression> expr;
    UnOp(Operator op, std::unique_ptr<Expression> &expr) : op(op), expr(std::move(expr)) {}
  };

  class Var : public Expression {
  public:
    std::string id;
    Var(std::string &id) : id(id) {}
  };

  class Integer : public Expression {
  public:
    int val;
    Integer(int val) : val(val) {};
  };


  /* STATEMENTS */
  class Statement : public Node {};

  class VarDecl : public Statement {
  public:
    std::unique_ptr<Var> var;
    DataType dataType;  
    VarDecl(std::unique_ptr<Var> &var, DataType dataType)
      : var(std::move(var)), dataType(dataType) {}
  };

  class VarAssign : public Statement {
  public:
    std::unique_ptr<Var> var;
    std::unique_ptr<Expression> expr;
    VarAssign(std::unique_ptr<Var> &var, std::unique_ptr<Expression> &expr)
    : var(std::move(var)), expr(std::move(expr)) {}
  };

  class StatementList : public Statement {
  public:
    std::vector<std::unique_ptr<Statement> > statements;
    StatementList() {}
    void addStatement(std::unique_ptr<Statement> stmt) {
      statements.push_back(std::move(stmt));
    }
  };
}