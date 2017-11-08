static inline int is_daemon_excluded(const char *fname, int is_dir)
{
	if (daemon_filter_list.head
	 && check_filter(&daemon_filter_list, FLOG, fname, is_dir) < 0) {
		errno = ENOENT;
		return 1;
	}
	return 0;
}