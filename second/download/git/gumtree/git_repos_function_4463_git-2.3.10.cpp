static void stuff_change(struct diff_options *opt,
			 unsigned old_mode, unsigned new_mode,
			 const unsigned char *old_sha1,
			 const unsigned char *new_sha1,
			 int old_sha1_valid,
			 int new_sha1_valid,
			 const char *old_name,
			 const char *new_name)
{
	struct diff_filespec *one, *two;

	if (!is_null_sha1(old_sha1) && !is_null_sha1(new_sha1) &&
	    !hashcmp(old_sha1, new_sha1) && (old_mode == new_mode))
		return;

	if (DIFF_OPT_TST(opt, REVERSE_DIFF)) {
		unsigned tmp;
		const unsigned char *tmp_u;
		const char *tmp_c;
		tmp = old_mode; old_mode = new_mode; new_mode = tmp;
		tmp_u = old_sha1; old_sha1 = new_sha1; new_sha1 = tmp_u;
		tmp_c = old_name; old_name = new_name; new_name = tmp_c;
	}

	if (opt->prefix &&
	    (strncmp(old_name, opt->prefix, opt->prefix_length) ||
	     strncmp(new_name, opt->prefix, opt->prefix_length)))
		return;

	one = alloc_filespec(old_name);
	two = alloc_filespec(new_name);
	fill_filespec(one, old_sha1, old_sha1_valid, old_mode);
	fill_filespec(two, new_sha1, new_sha1_valid, new_mode);

	diff_queue(&diff_queued_diff, one, two);
}