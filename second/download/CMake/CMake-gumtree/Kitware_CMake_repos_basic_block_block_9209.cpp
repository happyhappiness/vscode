(!RB_SENTINEL_P(tmp)) {
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