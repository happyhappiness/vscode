{
	archive_rbto_compare_key_fn compare_key = rbt->rbt_ops->rbto_compare_key;
	struct archive_rb_node *parent = rbt->rbt_root;
	struct archive_rb_node *last = NULL;

	while (!RB_SENTINEL_P(parent)) {
		const signed int diff = (*compare_key)(parent, key);
		if (diff == 0)
			return parent;
		if (diff > 0)
			last = parent;
		parent = parent->rb_nodes[diff > 0];
	}

	return last;
}