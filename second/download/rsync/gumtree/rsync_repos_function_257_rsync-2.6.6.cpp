char *partial_dir_fname(const char *fname)
{
	char *t = partial_fname;
	int sz = sizeof partial_fname;
	const char *fn;

	if ((fn = strrchr(fname, '/')) != NULL) {
		fn++;
		if (*partial_dir != '/') {
			int len = fn - fname;
			strncpy(t, fname, len); /* safe */
			t += len;
			sz -= len;
		}
	} else
		fn = fname;
	if ((int)pathjoin(t, sz, partial_dir, fn) >= sz)
		return NULL;
	if (server_filter_list.head) {
		static int len;
		if (!len)
			len = strlen(partial_dir);
		t[len] = '\0';
		if (check_filter(&server_filter_list, partial_fname, 1) < 0)
			return NULL;
		t[len] = '/';
		if (check_filter(&server_filter_list, partial_fname, 0) < 0)
			return NULL;
	}

	return partial_fname;
}