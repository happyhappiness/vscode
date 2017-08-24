{
		const int rebalance = RB_BLACK_P(self) && !RB_ROOT_P(rbt, self);
		__archive_rb_tree_prune_node(rbt, self, rebalance);
		return;
	}