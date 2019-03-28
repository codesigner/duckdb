//===----------------------------------------------------------------------===//
//                         DuckDB
//
// planner/expression.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "parser/base_expression.hpp"

namespace duckdb {
//!  The Expression class represents a bound Expression with a return type
class Expression : public BaseExpression {
public:
	Expression(ExpressionType type, ExpressionClass expression_class, TypeId return_type, SQLType sql_type);

	//! The return type of the expression
	TypeId return_type;
	//! The SQL type of the expression
	SQLType sql_type;
public:
	bool IsAggregate() const override;
	bool IsWindow() const override;
	bool HasSubquery() const override;
	bool IsScalar() const override;
	bool HasParameter() const override;
	bool IsFoldable() {
		return IsScalar() && !IsAggregate() && !IsWindow() && !HasParameter();
	}

	uint64_t Hash() const override;

	static bool Equals(Expression *left, Expression *right) {
		return BaseExpression::Equals((BaseExpression *)left, (BaseExpression *)right);
	}
	//! Create a copy of this expression
	virtual unique_ptr<Expression> Copy() = 0;

protected:
	//! Copy base Expression properties from another expression to this one,
	//! used in Copy method
	void CopyProperties(Expression &other) {
		type = other.type;
		expression_class = other.expression_class;
		alias = other.alias;
		return_type = other.return_type;
	}
};

} // namespace duckdb