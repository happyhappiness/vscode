(!RB_SENTINEL_P(parent)) {
		const signed int diff = (*compare_key)(parent, key);
		if (diff == 0)
			return parent;
		if (diff < 0)
			last = parent;
		parent = parent->rb_nodes[diff > 0];
	}