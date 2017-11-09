static void log_setup_revisions_tweak(struct rev_info *rev,
				      struct setup_revision_opt *opt)
{
	if (DIFF_OPT_TST(&rev->diffopt, DEFAULT_FOLLOW_RENAMES) &&
	    rev->prune_data.nr == 1)
		DIFF_OPT_SET(&rev->diffopt, FOLLOW_RENAMES);

	/* Turn --cc/-c into -p --cc/-c when -p was not given */
	if (!rev->diffopt.output_format && rev->combine_merges)
		rev->diffopt.output_format = DIFF_FORMAT_PATCH;

	/* Turn -m on when --cc/-c was given */
	if (rev->combine_merges)
		rev->ignore_merges = 0;
}