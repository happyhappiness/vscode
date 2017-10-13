int read_index_from(struct index_state *istate, const char *path)
{
	struct split_index *split_index;
	int ret;

	/* istate->initialized covers both .git/index and .git/sharedindex.xxx */
	if (istate->initialized)
		return istate->cache_nr;

	ret = do_read_index(istate, path, 0);

	split_index = istate->split_index;
	if (!split_index || is_null_sha1(split_index->base_sha1)) {
		post_read_index_from(istate);
		return ret;
	}

	if (split_index->base)
		discard_index(split_index->base);
	else
		split_index->base = xcalloc(1, sizeof(*split_index->base));
	ret = do_read_index(split_index->base,
			    git_path("sharedindex.%s",
				     sha1_to_hex(split_index->base_sha1)), 1);
	if (hashcmp(split_index->base_sha1, split_index->base->sha1))
		die("broken index, expect %s in %s, got %s",
		    sha1_to_hex(split_index->base_sha1),
		    git_path("sharedindex.%s",
			     sha1_to_hex(split_index->base_sha1)),
		    sha1_to_hex(split_index->base->sha1));
	merge_base_index(istate);
	post_read_index_from(istate);
	return ret;
}