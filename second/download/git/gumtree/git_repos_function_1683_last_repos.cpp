int diff_result_code(struct diff_options *opt, int status)
{
	int result = 0;

	diff_warn_rename_limit("diff.renameLimit",
			       opt->needed_rename_limit,
			       opt->degraded_cc_to_c);
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    !(opt->output_format & DIFF_FORMAT_CHECKDIFF))
		return status;
	if (DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    DIFF_OPT_TST(opt, HAS_CHANGES))
		result |= 01;
	if ((opt->output_format & DIFF_FORMAT_CHECKDIFF) &&
	    DIFF_OPT_TST(opt, CHECK_FAILED))
		result |= 02;
	return result;
}