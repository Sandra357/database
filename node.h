#pragma once

class Node {
public:
	virtual Evaluate(Date d, Event e) const = 0;
};

class EmptyNode{
public:
	virtual string Evaluate(Date d, Event e) const override;
};


class DateComparisonNode{
public:
	DateComparisonNode(Comparison c, Date d);
	virtual string Evaluate() const override;

private:
	Comparison cmp;
	Date date;
};
/*
class EventComparisonNode{};
class LogicalOperationNode{};
*/