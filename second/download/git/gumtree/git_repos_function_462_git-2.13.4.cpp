static int too_many_rename_candidates(int num_create,
				      struct diff_options *options)
{
	int rename_limit = options->rename_limit;
	int num_src = rename_src_nr;
	int i;

	options->needed_rename_limit = 0;

	/*
	 * This basically does a test for the rename matrix not
	 * growing larger than a "rename_limit" square matrix, ie:
	 *
	 *    num_create * num_src > rename_limit * rename_limit
	 *
	 * but handles the potential overflow case specially (and we
	 * assume at least 32-bit integers)
	 */
	if (rename_limit <= 0 || rename_limit > 32767)
		rename_limit = 32767;
	if ((num_create <= rename_limit || num_src <= rename_limit) &&
	    (num_create * num_src <= rename_limit * rename_limit))
		return 0;

	options->needed_rename_limit =
		num_src > num_create ? num_src : num_create;

	/* Are we running under -C -C? */
	if (!DIFF_OPT_TST(options, FIND_COPIES_HARDER))
		return 1;

	/* Would we bust the limit if we were running under -C? */
	for (num_src = i = 0; i < rename_src_nr; i++) {
		if (diff_unmodified_pair(rename_src[i].p))
			continue;
		num_src++;
	}
	if ((num_create <= rename_limit || num_src <= rename_limit) &&
	    (num_create * num_src <= rename_limit * rename_limit))
		return 2;
	return 1;
}