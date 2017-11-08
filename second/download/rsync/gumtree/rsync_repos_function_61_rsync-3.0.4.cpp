void change_local_filter_dir(const char *dname, int dlen, int dir_depth)
{
	static int cur_depth = -1;
	static void *filt_array[MAXPATHLEN/2+1];

	if (!dname) {
		for ( ; cur_depth >= 0; cur_depth--) {
			if (filt_array[cur_depth]) {
				pop_local_filters(filt_array[cur_depth]);
				filt_array[cur_depth] = NULL;
			}
		}
		return;
	}

	assert(dir_depth < MAXPATHLEN/2+1);

	for ( ; cur_depth >= dir_depth; cur_depth--) {
		if (filt_array[cur_depth]) {
			pop_local_filters(filt_array[cur_depth]);
			filt_array[cur_depth] = NULL;
		}
	}

	cur_depth = dir_depth;
	filt_array[cur_depth] = push_local_filters(dname, dlen);
}