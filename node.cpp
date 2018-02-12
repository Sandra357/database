#include "node.h"

bool EmptyNode::Evaluate(Date d, string e) const {
	return true;
}

DateComparisonNode::DateComparisonNode(Comparison c, Date d) : cmp(c), date(d) {};

bool DateComparisonNode::Evaluate(Date d, string e) const {
	return d == date;
}

EventComparisonNode::EventComparisonNode(Comparison c, string e) : cmp(c), event(e) {};

bool EventComparisonNode::Evaluate(Date d, string e) const {
	return e == event;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation l_op,
										   shared_ptr<Node> l_node,
										   shared_ptr<Node> r_node)
				: logical_op(l_op), left_node(l_node), right_node(r_node) {};

bool LogicalOperationNode::Evaluate(Date d, string e) const {
	if(logical_op == LogicalOperation::And) {
		return left_node->Evaluate(d, e) && right_node->Evaluate(d, e);
	} else {
		return left_node->Evaluate(d, e) || right_node->Evaluate(d, e);
	}
}