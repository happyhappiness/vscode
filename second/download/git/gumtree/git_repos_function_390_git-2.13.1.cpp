int write_locked_index(struct index_state *istate, struct lock_file *lock,
		       unsigned flags)
{
	int new_shared_index, ret;
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
	if (too_many_not_shared_entries(istate))
		istate->cache_changed |= SPLIT_INDEX_ORDERED;

	new_shared_index = istate->cache_changed & SPLIT_INDEX_ORDERED;

	if (new_shared_index) {
		ret = write_shared_index(istate, lock, flags);
		if (ret)
			return ret;
	}

	ret = write_split_index(istate, lock, flags);

	/* Freshen the shared index only if the split-index was written */
	if (!ret && !new_shared_index)
		freshen_shared_index(sha1_to_hex(si->base_sha1), 1);

	return ret;
}