int read_index_from(struct index_state *istate, const char *path)
{
	struct split_index *split_index;
	int ret;
	char *base_sha1_hex;
	const char *base_path;

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

	base_sha1_hex = sha1_to_hex(split_index->base_sha1);
	base_path = git_path("sharedindex.%s", base_sha1_hex);
	ret = do_read_index(split_index->base, base_path, 1);
	if (hashcmp(split_index->base_sha1, split_index->base->sha1))
		die("broken index, expect %s in %s, got %s",
		    base_sha1_hex, base_path,
		    sha1_to_hex(split_index->base->sha1));

	freshen_shared_index(base_sha1_hex, 0);
	merge_base_index(istate);
	post_read_index_from(istate);
	return ret;
}