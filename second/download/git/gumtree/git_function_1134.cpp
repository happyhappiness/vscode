static void collect_changed_submodules(struct string_list *changed,
				       struct argv_array *argv)
{
	struct rev_info rev;
	const struct commit *commit;

	init_revisions(&rev, NULL);
	setup_revisions(argv->argc, argv->argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	while ((commit = get_revision(&rev))) {
		struct rev_info diff_rev;

		init_revisions(&diff_rev, NULL);
		diff_rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
		diff_rev.diffopt.format_callback = collect_changed_submodules_cb;
		diff_rev.diffopt.format_callback_data = changed;
		diff_tree_combined_merge(commit, 1, &diff_rev);
	}

	reset_revision_walk();
}