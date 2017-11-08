static int remove_file(struct merge_options *o, int clean,
		       const char *path, int no_wd)
{
	int update_cache = o->call_depth || clean;
	int update_working_directory = !o->call_depth && !no_wd;

	if (update_cache) {
		if (remove_file_from_cache(path))
			return -1;
	}
	if (update_working_directory) {
		if (ignore_case) {
			struct cache_entry *ce;
			ce = cache_file_exists(path, strlen(path), ignore_case);
			if (ce && ce_stage(ce) == 0)
				return 0;
		}
		if (remove_path(path))
			return -1;
	}
	return 0;
}