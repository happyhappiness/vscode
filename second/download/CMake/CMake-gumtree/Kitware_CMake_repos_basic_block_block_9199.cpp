(!RB_SENTINEL_P(parent)) {
		const signed int diff = (*compare_key)(parent, key);
		if (diff == 0)
			return parent;
		parent = parent->rb_nodes[diff > 0];
	}