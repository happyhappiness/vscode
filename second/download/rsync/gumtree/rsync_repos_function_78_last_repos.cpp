static void teardown_mergelist(filter_rule *ex)
{
	int j;

	if (!ex->u.mergelist)
		return;

	if (DEBUG_GTE(FILTER, 2)) {
		rprintf(FINFO, "[%s] deactivating mergelist #%d%s\n",
			who_am_i(), mergelist_cnt - 1,
			ex->u.mergelist->debug_type);
	}

	free(ex->u.mergelist->debug_type);
	free(ex->u.mergelist);

	for (j = 0; j < mergelist_cnt; j++) {
		if (mergelist_parents[j] == ex) {
			mergelist_parents[j] = NULL;
			break;
		}
	}
	while (mergelist_cnt && mergelist_parents[mergelist_cnt-1] == NULL)
		mergelist_cnt--;
}