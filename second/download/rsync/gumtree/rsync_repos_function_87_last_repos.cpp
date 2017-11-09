void pop_local_filters(void *mem)
{
	struct local_filter_state *pop = (struct local_filter_state *)mem;
	int i;
	int old_mergelist_cnt = pop ? pop->mergelist_cnt : 0;

	if (DEBUG_GTE(FILTER, 2))
		rprintf(FINFO, "[%s] popping local filters\n", who_am_i());

	for (i = mergelist_cnt; i-- > 0; ) {
		filter_rule *ex = mergelist_parents[i];
		filter_rule_list *lp;
		if (!ex)
			continue;
		lp = ex->u.mergelist;

		if (DEBUG_GTE(FILTER, 2)) {
			rprintf(FINFO, "[%s] popping mergelist #%d%s\n",
				who_am_i(), i, lp->debug_type);
		}

		pop_filter_list(lp);
		if (i >= old_mergelist_cnt && lp->head) {
			/* This mergelist does not exist in the state to be restored, but it
			 * still has inherited rules.  This can sometimes happen if a per-dir
			 * merge file calls setup_merge_file() in push_local_filters() and that
			 * leaves some inherited rules that aren't in the pushed list state. */
			if (DEBUG_GTE(FILTER, 2)) {
				rprintf(FINFO, "[%s] freeing parent_dirscan filters of mergelist #%d%s\n",
					who_am_i(), i, ex->u.mergelist->debug_type);
			}
			pop_filter_list(lp);
		}
	}

	if (!pop)
		return; /* No state to restore. */

	for (i = 0; i < old_mergelist_cnt; i++) {
		filter_rule *ex = mergelist_parents[i];
		if (!ex)
			continue;
		memcpy(ex->u.mergelist, &pop->mergelists[i], sizeof (filter_rule_list));
	}

	free(pop);
}