static void cmd_log_init_defaults(struct rev_info *rev)
{
	if (fmt_pretty)
		get_commit_format(fmt_pretty, rev);
	rev->verbose_header = 1;
	DIFF_OPT_SET(&rev->diffopt, RECURSIVE);
	rev->diffopt.stat_width = -1; /* use full terminal width */
	rev->diffopt.stat_graph_width = -1; /* respect statGraphWidth config */
	rev->abbrev_commit = default_abbrev_commit;
	rev->show_root_diff = default_show_root;
	rev->subject_prefix = fmt_patch_subject_prefix;
	DIFF_OPT_SET(&rev->diffopt, ALLOW_TEXTCONV);

	if (default_date_mode)
		rev->date_mode = parse_date_format(default_date_mode);
	rev->diffopt.touched_flags = 0;
}