static void show_new_file(struct rev_info *revs,
			  const struct cache_entry *new,
			  int cached, int match_missing)
{
	const unsigned char *sha1;
	unsigned int mode;
	unsigned dirty_submodule = 0;

	/*
	 * New file in the index: it might actually be different in
	 * the working tree.
	 */
	if (get_stat_data(new, &sha1, &mode, cached, match_missing,
	    &dirty_submodule, &revs->diffopt) < 0)
		return;

	diff_index_show_file(revs, "+", new, sha1, !is_null_sha1(sha1), mode, dirty_submodule);
}