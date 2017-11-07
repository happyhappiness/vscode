static int split_commit_in_progress(struct wt_status *s)
{
	int split_in_progress = 0;
	char *head = read_line_from_git_path("HEAD");
	char *orig_head = read_line_from_git_path("ORIG_HEAD");
	char *rebase_amend = read_line_from_git_path("rebase-merge/amend");
	char *rebase_orig_head = read_line_from_git_path("rebase-merge/orig-head");

	if (!head || !orig_head || !rebase_amend || !rebase_orig_head ||
	    !s->branch || strcmp(s->branch, "HEAD"))
		return split_in_progress;

	if (!strcmp(rebase_amend, rebase_orig_head)) {
		if (strcmp(head, rebase_amend))
			split_in_progress = 1;
	} else if (strcmp(orig_head, rebase_orig_head)) {
		split_in_progress = 1;
	}

	if (!s->amend && !s->nowarn && !s->workdir_dirty)
		split_in_progress = 0;

	free(head);
	free(orig_head);
	free(rebase_amend);
	free(rebase_orig_head);
	return split_in_progress;
}