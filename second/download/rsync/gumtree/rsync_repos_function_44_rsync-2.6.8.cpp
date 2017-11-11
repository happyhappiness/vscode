void pop_local_filters(void *mem)
{
	struct filter_list_struct *ap, *pop = (struct filter_list_struct*)mem;
	int i;

	for (i = mergelist_cnt; i-- > 0; ) {
		struct filter_struct *ex = mergelist_parents[i];
		struct filter_list_struct *lp = ex->u.mergelist;

		if (verbose > 2) {
			rprintf(FINFO, "[%s] popping filter list%s\n",
				who_am_i(), lp->debug_type);
		}

		clear_filter_list(lp);
	}

	if (!pop)
		return;

	for (i = 0, ap = pop; i < mergelist_cnt; i++) {
		memcpy(mergelist_parents[i]->u.mergelist, ap++,
		       sizeof (struct filter_list_struct));
	}

	free(pop);
}