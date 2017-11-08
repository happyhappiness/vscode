static void wt_status_collect_changes_worktree(struct wt_status *s)
{
	struct rev_info rev;

	init_revisions(&rev, NULL);
	setup_revisions(0, NULL, &rev, NULL);
	rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
	DIFF_OPT_SET(&rev.diffopt, DIRTY_SUBMODULES);
	rev.diffopt.ita_invisible_in_index = 1;
	if (!s->show_untracked_files)
		DIFF_OPT_SET(&rev.diffopt, IGNORE_UNTRACKED_IN_SUBMODULES);
	if (s->ignore_submodule_arg) {
		DIFF_OPT_SET(&rev.diffopt, OVERRIDE_SUBMODULE_CONFIG);
		handle_ignore_submodules_arg(&rev.diffopt, s->ignore_submodule_arg);
	}
	rev.diffopt.format_callback = wt_status_collect_changed_cb;
	rev.diffopt.format_callback_data = s;
	copy_pathspec(&rev.prune_data, &s->pathspec);
	run_diff_files(&rev, 0);
}