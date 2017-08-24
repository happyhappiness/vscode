(a->todo & TODO_OWNER) {
		int r2 = set_ownership(a);
		if (r2 < ret) ret = r2;
	}