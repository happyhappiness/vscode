static void write_index_patch(const struct am_state *state)
{
	struct tree *tree;
	struct object_id head;
	struct rev_info rev_info;
	FILE *fp;

	if (!get_sha1_tree("HEAD", head.hash))
		tree = lookup_tree(head.hash);
	else
		tree = lookup_tree(EMPTY_TREE_SHA1_BIN);

	fp = xfopen(am_path(state, "patch"), "w");
	init_revisions(&rev_info, NULL);
	rev_info.diff = 1;
	rev_info.disable_stdin = 1;
	rev_info.no_commit_id = 1;
	rev_info.diffopt.output_format = DIFF_FORMAT_PATCH;
	rev_info.diffopt.use_color = 0;
	rev_info.diffopt.file = fp;
	rev_info.diffopt.close_file = 1;
	add_pending_object(&rev_info, &tree->object, "");
	diff_setup_done(&rev_info.diffopt);
	run_diff_index(&rev_info, 1);
}