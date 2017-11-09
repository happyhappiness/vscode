int is_excluded_from_list(const char *pathname,
			  int pathlen, const char *basename, int *dtype,
			  struct exclude_list *el, struct index_state *istate)
{
	struct exclude *exclude;
	exclude = last_exclude_matching_from_list(pathname, pathlen, basename,
						  dtype, el, istate);
	if (exclude)
		return exclude->flags & EXC_FLAG_NEGATIVE ? 0 : 1;
	return -1; /* undecided */
}