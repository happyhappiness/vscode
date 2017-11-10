static void wt_status_collect_changes_index(struct wt_status *s)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_revisions(&rev, NULL);
	memset(&opt, 0, sizeof(opt));
	opt.def = s->is_initial ? EMPTY_TREE_SHA1_HEX : s->reference;
	setup_revisions(0, NULL, &rev, &opt);

	DIFF_OPT_SET(&rev.diffopt, OVERRIDE_SUBMODULE_CONFIG);
	rev.diffopt.ita_invisible_in_index = 1;
	if (s->ignore_submodule_arg) {
		handle_ignore_submodules_arg(&rev.diffopt, s->ignore_submodule_arg);
	} else {
		/*
		 * Unless the user did explicitly request a submodule ignore
		 * mode by passing a command line option we do not ignore any
		 * changed submodule SHA-1s when comparing index and HEAD, no
		 * matter what is configured. Otherwise the user won't be
		 * shown any submodules she manually added (and which are
		 * staged to be committed), which would be really confusing.
		 */
		handle_ignore_submodules_arg(&rev.diffopt, "dirty");
	}

	rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = wt_status_collect_updated_cb;
	rev.diffopt.format_callback_data = s;
	rev.diffopt.detect_rename = 1;
	rev.diffopt.rename_limit = 200;
	rev.diffopt.break_opt = 0;
	copy_pathspec(&rev.prune_data, &s->pathspec);
	run_diff_index(&rev, 1);
}