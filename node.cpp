#include "node.h"

virtual string EmptyNode::Evaluate(Date d, Event e) const override {
	return "";
}

DateComparisonNode::DateComparisonNode(Comparison c, Date d) : cmp(c), date(d) {};

virtual string DateComparisonNode::Evaluate(Date d, Event e) const override {

}

/*

class EventComparisonNode{};
class LogicalOperationNode{};
*/