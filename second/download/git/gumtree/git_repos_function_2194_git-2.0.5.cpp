void setup_unpack_trees_porcelain(struct unpack_trees_options *opts,
				  const char *cmd)
{
	int i;
	const char **msgs = opts->msgs;
	const char *msg;
	char *tmp;
	const char *cmd2 = strcmp(cmd, "checkout") ? cmd : "switch branches";
	if (advice_commit_before_merge)
		msg = "Your local changes to the following files would be overwritten by %s:\n%%s"
			"Please, commit your changes or stash them before you can %s.";
	else
		msg = "Your local changes to the following files would be overwritten by %s:\n%%s";
	tmp = xmalloc(strlen(msg) + strlen(cmd) + strlen(cmd2) - 2);
	sprintf(tmp, msg, cmd, cmd2);
	msgs[ERROR_WOULD_OVERWRITE] = tmp;
	msgs[ERROR_NOT_UPTODATE_FILE] = tmp;

	msgs[ERROR_NOT_UPTODATE_DIR] =
		"Updating the following directories would lose untracked files in it:\n%s";

	if (advice_commit_before_merge)
		msg = "The following untracked working tree files would be %s by %s:\n%%s"
			"Please move or remove them before you can %s.";
	else
		msg = "The following untracked working tree files would be %s by %s:\n%%s";
	tmp = xmalloc(strlen(msg) + strlen(cmd) + strlen("removed") + strlen(cmd2) - 4);
	sprintf(tmp, msg, "removed", cmd, cmd2);
	msgs[ERROR_WOULD_LOSE_UNTRACKED_REMOVED] = tmp;
	tmp = xmalloc(strlen(msg) + strlen(cmd) + strlen("overwritten") + strlen(cmd2) - 4);
	sprintf(tmp, msg, "overwritten", cmd, cmd2);
	msgs[ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN] = tmp;

	/*
	 * Special case: ERROR_BIND_OVERLAP refers to a pair of paths, we
	 * cannot easily display it as a list.
	 */
	msgs[ERROR_BIND_OVERLAP] = "Entry '%s' overlaps with '%s'.  Cannot bind.";

	msgs[ERROR_SPARSE_NOT_UPTODATE_FILE] =
		"Cannot update sparse checkout: the following entries are not up-to-date:\n%s";
	msgs[ERROR_WOULD_LOSE_ORPHANED_OVERWRITTEN] =
		"The following Working tree files would be overwritten by sparse checkout update:\n%s";
	msgs[ERROR_WOULD_LOSE_ORPHANED_REMOVED] =
		"The following Working tree files would be removed by sparse checkout update:\n%s";

	opts->show_all_errors = 1;
	/* rejected paths may not have a static buffer */
	for (i = 0; i < ARRAY_SIZE(opts->unpack_rejects); i++)
		opts->unpack_rejects[i].strdup_strings = 1;
}