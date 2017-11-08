static void stuff_change(struct diff_options *opt,
			 unsigned old_mode, unsigned new_mode,
			 const struct object_id *old_oid,
			 const struct object_id *new_oid,
			 int old_oid_valid,
			 int new_oid_valid,
			 const char *old_name,
			 const char *new_name)
{
	struct diff_filespec *one, *two;

	if (!is_null_oid(old_oid) && !is_null_oid(new_oid) &&
	    !oidcmp(old_oid, new_oid) && (old_mode == new_mode))
		return;

	if (DIFF_OPT_TST(opt, REVERSE_DIFF)) {
		SWAP(old_mode, new_mode);
		SWAP(old_oid, new_oid);
		SWAP(old_name, new_name);
	}

	if (opt->prefix &&
	    (strncmp(old_name, opt->prefix, opt->prefix_length) ||
	     strncmp(new_name, opt->prefix, opt->prefix_length)))
		return;

	one = alloc_filespec(old_name);
	two = alloc_filespec(new_name);
	fill_filespec(one, old_oid->hash, old_oid_valid, old_mode);
	fill_filespec(two, new_oid->hash, new_oid_valid, new_mode);

	diff_queue(&diff_queued_diff, one, two);
}