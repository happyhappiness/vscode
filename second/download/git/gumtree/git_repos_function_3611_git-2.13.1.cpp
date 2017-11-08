static void calculate_changed_submodule_paths(void)
{
	struct rev_info rev;
	struct commit *commit;
	struct argv_array argv = ARGV_ARRAY_INIT;

	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(NULL, NULL))
		return;

	init_revisions(&rev, NULL);
	argv_array_push(&argv, "--"); /* argv[0] program name */
	oid_array_for_each_unique(&ref_tips_after_fetch,
				   add_oid_to_argv, &argv);
	argv_array_push(&argv, "--not");
	oid_array_for_each_unique(&ref_tips_before_fetch,
				   add_oid_to_argv, &argv);
	setup_revisions(argv.argc, argv.argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	/*
	 * Collect all submodules (whether checked out or not) for which new
	 * commits have been recorded upstream in "changed_submodule_paths".
	 */
	while ((commit = get_revision(&rev))) {
		struct commit_list *parent = commit->parents;
		while (parent) {
			struct diff_options diff_opts;
			diff_setup(&diff_opts);
			DIFF_OPT_SET(&diff_opts, RECURSIVE);
			diff_opts.output_format |= DIFF_FORMAT_CALLBACK;
			diff_opts.format_callback = submodule_collect_changed_cb;
			diff_setup_done(&diff_opts);
			diff_tree_sha1(parent->item->object.oid.hash, commit->object.oid.hash, "", &diff_opts);
			diffcore_std(&diff_opts);
			diff_flush(&diff_opts);
			parent = parent->next;
		}
	}

	argv_array_clear(&argv);
	oid_array_clear(&ref_tips_before_fetch);
	oid_array_clear(&ref_tips_after_fetch);
	initialized_fetch_ref_tips = 0;
}