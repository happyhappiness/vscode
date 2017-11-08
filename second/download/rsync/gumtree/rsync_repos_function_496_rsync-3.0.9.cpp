static inline int path_is_daemon_excluded(char *path, int ignore_filename)
{
	if (daemon_filter_list.head) {
		char *slash = path;

		while ((slash = strchr(slash+1, '/')) != NULL) {
			int ret;
			*slash = '\0';
			ret = check_filter(&daemon_filter_list, FLOG, path, 1);
			*slash = '/';
			if (ret < 0) {
				errno = ENOENT;
				return 1;
			}
		}

		if (!ignore_filename
		 && check_filter(&daemon_filter_list, FLOG, path, 1) < 0) {
			errno = ENOENT;
			return 1;
		}
	}

	return 0;
}