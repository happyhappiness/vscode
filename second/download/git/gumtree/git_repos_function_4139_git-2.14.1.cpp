int read_tree(struct tree *tree, int stage, struct pathspec *match,
	      struct index_state *istate)
{
	read_tree_fn_t fn = NULL;
	int i, err;

	/*
	 * Currently the only existing callers of this function all
	 * call it with stage=1 and after making sure there is nothing
	 * at that stage; we could always use read_one_entry_quick().
	 *
	 * But when we decide to straighten out git-read-tree not to
	 * use unpack_trees() in some cases, this will probably start
	 * to matter.
	 */

	/*
	 * See if we have cache entry at the stage.  If so,
	 * do it the original slow way, otherwise, append and then
	 * sort at the end.
	 */
	for (i = 0; !fn && i < istate->cache_nr; i++) {
		const struct cache_entry *ce = istate->cache[i];
		if (ce_stage(ce) == stage)
			fn = read_one_entry;
	}

	if (!fn)
		fn = read_one_entry_quick;
	err = read_tree_recursive(tree, "", 0, stage, match, fn, istate);
	if (fn == read_one_entry || err)
		return err;

	/*
	 * Sort the cache entry -- we need to nuke the cache tree, though.
	 */
	cache_tree_free(&istate->cache_tree);
	QSORT(istate->cache, istate->cache_nr, cmp_cache_name_compare);
	return 0;
}