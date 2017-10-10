
struct update_callback_data {
	int flags;
	int add_errors;
};

static void chmod_pathspec(struct pathspec *pathspec, int force_mode)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];

		if (pathspec && !ce_path_match(ce, pathspec, NULL))
			continue;

		if (chmod_cache_entry(ce, force_mode) < 0)
			fprintf(stderr, "cannot chmod '%s'", ce->name);
	}
}

static int fix_unmerged_status(struct diff_filepair *p,
			       struct update_callback_data *data)
{
