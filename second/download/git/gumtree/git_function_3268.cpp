struct tree *write_tree_from_memory(struct merge_options *o)
{
	struct tree *result = NULL;

	if (unmerged_cache()) {
		int i;
		fprintf(stderr, "BUG: There are unmerged index entries:\n");
		for (i = 0; i < active_nr; i++) {
			const struct cache_entry *ce = active_cache[i];
			if (ce_stage(ce))
				fprintf(stderr, "BUG: %d %.*s\n", ce_stage(ce),
					(int)ce_namelen(ce), ce->name);
		}
		die("Bug in merge-recursive.c");
	}

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree) &&
	    cache_tree_update(&the_index, 0) < 0)
		die(_("error building trees"));

	result = lookup_tree(active_cache_tree->sha1);

	return result;
}