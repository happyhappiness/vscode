	 * the fact that this object is involved in "write its base
	 * first before writing a deltified object" recursion.
	 */
	recursing = (e->idx.offset == 1);
	if (recursing) {
		warning("recursive delta detected for object %s",
			sha1_to_hex(e->idx.sha1));
		return WRITE_ONE_RECURSIVE;
	} else if (e->idx.offset || e->preferred_base) {
		/* offset is non zero if object is written already. */
		return WRITE_ONE_SKIP;
	}

