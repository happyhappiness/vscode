		isatty(0) && isatty(1) &&
		st_stdin.st_dev == st_stdout.st_dev &&
		st_stdin.st_ino == st_stdout.st_ino &&
		st_stdin.st_mode == st_stdout.st_mode);
}

static struct commit_list *collect_parents(struct commit *head_commit,
					   int *head_subsumed,
					   int argc, const char **argv)
{
	int i;
	struct commit_list *remoteheads = NULL, *parents, *next;
	struct commit_list **remotes = &remoteheads;

	if (head_commit)
		remotes = &commit_list_insert(head_commit, remotes)->next;
	for (i = 0; i < argc; i++) {
		struct commit *commit = get_merge_parent(argv[i]);
		if (!commit)
			help_unknown_ref(argv[i], "merge",
					 "not something we can merge");
		remotes = &commit_list_insert(commit, remotes)->next;
	}
	*remotes = NULL;

	parents = reduce_heads(remoteheads);

	*head_subsumed = 1; /* we will flip this to 0 when we find it */
	for (remoteheads = NULL, remotes = &remoteheads;
	     parents;
	     parents = next) {
		struct commit *commit = parents->item;
		next = parents->next;
		if (commit == head_commit)
			*head_subsumed = 0;
		else
			remotes = &commit_list_insert(commit, remotes)->next;
	}
	return remoteheads;
}

int cmd_merge(int argc, const char **argv, const char *prefix)
{
	unsigned char result_tree[20];
