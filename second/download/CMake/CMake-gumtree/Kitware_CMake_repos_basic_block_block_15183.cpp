(a->todo & TODO_XATTR) {
		int r2 = set_xattrs(a);
		if (r2 < ret) ret = r2;
	}