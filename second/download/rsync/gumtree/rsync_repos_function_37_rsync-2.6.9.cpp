static void free_filter(struct filter_struct *ex)
{
	if (ex->match_flags & MATCHFLG_PERDIR_MERGE) {
		free(ex->u.mergelist->debug_type);
		free(ex->u.mergelist);
		mergelist_cnt--;
	}
	free(ex->pattern);
	free(ex);
}