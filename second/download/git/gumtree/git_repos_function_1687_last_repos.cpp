void diff_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
		 const struct object_id *old_oid,
		 const struct object_id *new_oid,
		 int old_oid_valid, int new_oid_valid,
		 const char *concatpath,
		 unsigned old_dirty_submodule, unsigned new_dirty_submodule)
{
	struct diff_filespec *one, *two;
	struct diff_filepair *p;

	if (S_ISGITLINK(old_mode) && S_ISGITLINK(new_mode) &&
	    is_submodule_ignored(concatpath, options))
		return;

	if (DIFF_OPT_TST(options, REVERSE_DIFF)) {
		SWAP(old_mode, new_mode);
		SWAP(old_oid, new_oid);
		SWAP(old_oid_valid, new_oid_valid);
		SWAP(old_dirty_submodule, new_dirty_submodule);
	}

	if (options->prefix &&
	    strncmp(concatpath, options->prefix, options->prefix_length))
		return;

	one = alloc_filespec(concatpath);
	two = alloc_filespec(concatpath);
	fill_filespec(one, old_oid, old_oid_valid, old_mode);
	fill_filespec(two, new_oid, new_oid_valid, new_mode);
	one->dirty_submodule = old_dirty_submodule;
	two->dirty_submodule = new_dirty_submodule;
	p = diff_queue(&diff_queued_diff, one, two);

	if (DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		return;

	if (DIFF_OPT_TST(options, QUICK) && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(p))
		return;

	DIFF_OPT_SET(options, HAS_CHANGES);
}