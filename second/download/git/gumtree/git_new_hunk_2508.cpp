	refresh_cache(REFRESH_QUIET);

	if (write_locked_index(&the_index, &false_lock, CLOSE_LOCK))
		die(_("unable to write temporary index file"));

	discard_cache();
	ret = get_lock_file_path(&false_lock);
	read_cache_from(ret);
	return ret;
}

static int run_status(FILE *fp, const char *index_file, const char *prefix, int nowarn,
		      struct wt_status *s)
{
	unsigned char sha1[20];
