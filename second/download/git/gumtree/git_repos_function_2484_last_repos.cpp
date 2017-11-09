int is_excluded(struct dir_struct *dir, struct index_state *istate,
		const char *pathname, int *dtype_p)
{
	struct exclude *exclude =
		last_exclude_matching(dir, istate, pathname, dtype_p);
	if (exclude)
		return exclude->flags & EXC_FLAG_NEGATIVE ? 0 : 1;
	return 0;
}