static void write_commit_patch(const struct am_state *state, struct commit *commit)
{
	struct rev_info rev_info;
	FILE *fp;

	fp = xfopen(am_path(state, "patch"), "w");
	init_revisions(&rev_info, NULL);
	rev_info.diff = 1;
	rev_info.abbrev = 0;
	rev_info.disable_stdin = 1;
	rev_info.show_root_diff = 1;
	rev_info.diffopt.output_format = DIFF_FORMAT_PATCH;
	rev_info.no_commit_id = 1;
	DIFF_OPT_SET(&rev_info.diffopt, BINARY);
	DIFF_OPT_SET(&rev_info.diffopt, FULL_INDEX);
	rev_info.diffopt.use_color = 0;
	rev_info.diffopt.file = fp;
	rev_info.diffopt.close_file = 1;
	add_pending_object(&rev_info, &commit->object, "");
	diff_setup_done(&rev_info.diffopt);
	log_tree_commit(&rev_info, commit);
}