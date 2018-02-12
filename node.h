#pragma once

#include "date.h"

#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
	And,
	Or
};

class Node {
public:
	virtual bool Evaluate(Date& d, string& e) const = 0;
};

class EmptyNode : public Node {
public:
	virtual bool Evaluate(Date& d, string& e) const;
};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison& c, Date& d);
	virtual bool Evaluate(Date& d, string& e) const;

private:
	Comparison cmp;
	Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison& c, string& e);
	virtual bool Evaluate(Date& d, string& e) const;

private:
	Comparison cmp;
	string event;
};


class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation l_op,
						 shared_ptr<Node> l_node,
						 shared_ptr<Node> r_node);
	virtual bool Evaluate(Date& d, string& e) const;

private:
	LogicalOperation logical_op;
	shared_ptr<const Node> left_node;
	shared_ptr<const Node> right_node;
};
