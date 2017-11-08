static int dry_run_commit(int argc, const char **argv, const char *prefix,
			  const struct commit *current_head, struct wt_status *s)
{
	int commitable;
	const char *index_file;

	index_file = prepare_index(argc, argv, prefix, current_head, 1);
	commitable = run_status(stdout, index_file, prefix, 0, s);
	rollback_index_files();

	return commitable ? 0 : 1;
}