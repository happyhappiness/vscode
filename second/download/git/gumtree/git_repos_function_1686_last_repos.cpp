void diff_addremove(struct diff_options *options,
		    int addremove, unsigned mode,
		    const struct object_id *oid,
		    int oid_valid,
		    const char *concatpath, unsigned dirty_submodule)
{
	struct diff_filespec *one, *two;

	if (S_ISGITLINK(mode) && is_submodule_ignored(concatpath, options))
		return;

	/* This may look odd, but it is a preparation for
	 * feeding "there are unchanged files which should
	 * not produce diffs, but when you are doing copy
	 * detection you would need them, so here they are"
	 * entries to the diff-core.  They will be prefixed
	 * with something like '=' or '*' (I haven't decided
	 * which but should not make any difference).
	 * Feeding the same new and old to diff_change()
	 * also has the same effect.
	 * Before the final output happens, they are pruned after
	 * merged into rename/copy pairs as appropriate.
	 */
	if (DIFF_OPT_TST(options, REVERSE_DIFF))
		addremove = (addremove == '+' ? '-' :
			     addremove == '-' ? '+' : addremove);

	if (options->prefix &&
	    strncmp(concatpath, options->prefix, options->prefix_length))
		return;

	one = alloc_filespec(concatpath);
	two = alloc_filespec(concatpath);

	if (addremove != '+')
		fill_filespec(one, oid, oid_valid, mode);
	if (addremove != '-') {
		fill_filespec(two, oid, oid_valid, mode);
		two->dirty_submodule = dirty_submodule;
	}

	diff_queue(&diff_queued_diff, one, two);
	if (!DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		DIFF_OPT_SET(options, HAS_CHANGES);
}