static void wt_status_print_verbose(struct wt_status *s)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_revisions(&rev, NULL);
	DIFF_OPT_SET(&rev.diffopt, ALLOW_TEXTCONV);

	memset(&opt, 0, sizeof(opt));
	opt.def = s->is_initial ? EMPTY_TREE_SHA1_HEX : s->reference;
	setup_revisions(0, NULL, &rev, &opt);

	rev.diffopt.output_format |= DIFF_FORMAT_PATCH;
	rev.diffopt.detect_rename = 1;
	rev.diffopt.file = s->fp;
	rev.diffopt.close_file = 0;
	/*
	 * If we're not going to stdout, then we definitely don't
	 * want color, since we are going to the commit message
	 * file (and even the "auto" setting won't work, since it
	 * will have checked isatty on stdout). But we then do want
	 * to insert the scissor line here to reliably remove the
	 * diff before committing.
	 */
	if (s->fp != stdout) {
		rev.diffopt.use_color = 0;
		wt_status_add_cut_line(s->fp);
	}
	run_diff_index(&rev, 1);
}