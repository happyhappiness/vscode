{
		/*
		 * All new nodes are colored red.  We only need to rebalance
		 * if our parent is also red.
		 */
		RB_MARK_RED(self);
		rebalance = RB_RED_P(parent);
	}