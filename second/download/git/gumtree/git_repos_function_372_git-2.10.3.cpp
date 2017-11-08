int write_locked_index(struct index_state *istate, struct lock_file *lock,
		       unsigned flags)
{
	struct split_index *si = istate->split_index;

	if (!si || alternate_index_output ||
	    (istate->cache_changed & ~EXTMASK)) {
		if (si)
			hashclr(si->base_sha1);
		return do_write_locked_index(istate, lock, flags);
	}

	if (getenv("GIT_TEST_SPLIT_INDEX")) {
		int v = si->base_sha1[0];
		if ((v & 15) < 6)
			istate->cache_changed |= SPLIT_INDEX_ORDERED;
	}
	if (istate->cache_changed & SPLIT_INDEX_ORDERED) {
		int ret = write_shared_index(istate, lock, flags);
		if (ret)
			return ret;
	}

	return write_split_index(istate, lock, flags);
}