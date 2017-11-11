static int is_excluded(const char *fname, int is_dir, int filter_level)
{
#if 0 /* This currently never happens, so avoid a useless compare. */
	if (filter_level == NO_FILTERS)
		return 0;
#endif
	if (is_daemon_excluded(fname, is_dir))
		return 1;
	if (filter_level != ALL_FILTERS)
		return 0;
	if (filter_list.head
	    && check_filter(&filter_list, FINFO, fname, is_dir) < 0)
		return 1;
	return 0;
}