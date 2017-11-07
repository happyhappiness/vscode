void show_submodule_summary(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset)
{
	struct rev_info rev;
	struct commit *left = NULL, *right = NULL;
	struct commit_list *merge_bases = NULL;

	show_submodule_header(f, path, line_prefix, one, two, dirty_submodule,
			      meta, reset, &left, &right, &merge_bases);

	/*
	 * If we don't have both a left and a right pointer, there is no
	 * reason to try and display a summary. The header line should contain
	 * all the information the user needs.
	 */
	if (!left || !right)
		goto out;

	/* Treat revision walker failure the same as missing commits */
	if (prepare_submodule_summary(&rev, path, left, right, merge_bases)) {
		fprintf(f, "%s(revision walker failed)\n", line_prefix);
		goto out;
	}

	print_submodule_summary(&rev, f, line_prefix, del, add, reset);

out:
	if (merge_bases)
		free_commit_list(merge_bases);
	clear_commit_marks(left, ~0);
	clear_commit_marks(right, ~0);
}