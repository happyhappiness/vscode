static void mark_new_skip_worktree(struct exclude_list *el,
				   struct index_state *the_index,
				   int select_flag, int skip_wt_flag)
{
	int i;

	/*
	 * 1. Pretend the narrowest worktree: only unmerged entries
	 * are checked out
	 */
	for (i = 0; i < the_index->cache_nr; i++) {
		struct cache_entry *ce = the_index->cache[i];

		if (select_flag && !(ce->ce_flags & select_flag))
			continue;

		if (!ce_stage(ce))
			ce->ce_flags |= skip_wt_flag;
		else
			ce->ce_flags &= ~skip_wt_flag;
	}

	/*
	 * 2. Widen worktree according to sparse-checkout file.
	 * Matched entries will have skip_wt_flag cleared (i.e. "in")
	 */
	clear_ce_flags(the_index->cache, the_index->cache_nr,
		       select_flag, skip_wt_flag, el);
}