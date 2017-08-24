{
	archive_rbto_compare_nodes_fn compare_nodes = rbt->rbt_ops->rbto_compare_nodes;
	struct archive_rb_node *parent, *tmp;
	unsigned int position;
	int rebalance;

	tmp = rbt->rbt_root;
	/*
	 * This is a hack.  Because rbt->rbt_root is just a
	 * struct archive_rb_node *, just like rb_node->rb_nodes[RB_DIR_LEFT],
	 * we can use this fact to avoid a lot of tests for root and know
	 * that even at root, updating
	 * RB_FATHER(rb_node)->rb_nodes[RB_POSITION(rb_node)] will
	 * update rbt->rbt_root.
	 */
	parent = (struct archive_rb_node *)(void *)&rbt->rbt_root;
	position = RB_DIR_LEFT;

	/*
	 * Find out where to place this new leaf.
	 */
	while (!RB_SENTINEL_P(tmp)) {
		const signed int diff = (*compare_nodes)(tmp, self);
		if (diff == 0) {
			/*
			 * Node already exists; don't insert.
			 */
			return F;
		}
		parent = tmp;
		position = (diff > 0);
		tmp = parent->rb_nodes[position];
	}

	/*
	 * Initialize the node and insert as a leaf into the tree.
	 */
	RB_SET_FATHER(self, parent);
	RB_SET_POSITION(self, position);
	if (parent == (struct archive_rb_node *)(void *)&rbt->rbt_root) {
		RB_MARK_BLACK(self);		/* root is always black */
		rebalance = F;
	} else {
		/*
		 * All new nodes are colored red.  We only need to rebalance
		 * if our parent is also red.
		 */
		RB_MARK_RED(self);
		rebalance = RB_RED_P(parent);
	}
	self->rb_left = parent->rb_nodes[position];
	self->rb_right = parent->rb_nodes[position];
	parent->rb_nodes[position] = self;

	/*
	 * Rebalance tree after insertion
	 */
	if (rebalance)
		__archive_rb_tree_insert_rebalance(rbt, self);

	return T;
}