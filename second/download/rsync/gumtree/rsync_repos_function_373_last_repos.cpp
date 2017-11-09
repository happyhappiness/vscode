static inline void call_glob_match(const char *name, int len, int from_glob,
				   char *arg, int abpos, int fbpos)
{
	char *use_buf;

	ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, abpos + len + 2);
	memcpy(glob.arg_buf + abpos, name, len);
	abpos += len;
	glob.arg_buf[abpos] = '\0';

	if (fbpos >= 0) {
		ENSURE_MEMSPACE(glob.filt_buf, char, glob.fbsize, fbpos + len + 2);
		memcpy(glob.filt_buf + fbpos, name, len);
		fbpos += len;
		glob.filt_buf[fbpos] = '\0';
		use_buf = glob.filt_buf;
	} else
		use_buf = glob.arg_buf;

	if (from_glob || (arg && len)) {
		STRUCT_STAT st;
		int is_dir;

		if (do_stat(glob.arg_buf, &st) != 0)
			return;
		is_dir = S_ISDIR(st.st_mode) != 0;
		if (arg && !is_dir)
			return;

		if (daemon_filter_list.head
		 && check_filter(&daemon_filter_list, FLOG, use_buf, is_dir) < 0)
			return;
	}

	if (arg) {
		glob.arg_buf[abpos++] = '/';
		glob.arg_buf[abpos] = '\0';
		if (fbpos >= 0) {
			glob.filt_buf[fbpos++] = '/';
			glob.filt_buf[fbpos] = '\0';
		}
		glob_match(arg, abpos, fbpos);
	} else {
		ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, glob.argc + 1);
		if (!(glob.argv[glob.argc++] = strdup(glob.arg_buf)))
			out_of_memory("glob_match");
	}
}