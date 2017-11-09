static int oneway_diff(const struct cache_entry * const *src,
		       struct unpack_trees_options *o)
{
	const struct cache_entry *idx = src[0];
	const struct cache_entry *tree = src[1];
	struct rev_info *revs = o->unpack_data;

	/*
	 * Unpack-trees generates a DF/conflict entry if
	 * there was a directory in the index and a tree
	 * in the tree. From a diff standpoint, that's a
	 * delete of the tree and a create of the file.
	 */
	if (tree == o->df_conflict_entry)
		tree = NULL;

	if (ce_path_match(idx ? idx : tree, &revs->prune_data, NULL)) {
		do_oneway_diff(o, idx, tree);
		if (diff_can_quit_early(&revs->diffopt)) {
			o->exiting_early = 1;
			return -1;
		}
	}

	return 0;
}