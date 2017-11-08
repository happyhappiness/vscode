void setup_unpack_trees_porcelain(struct unpack_trees_options *opts,
				  const char *cmd)
{
	int i;
	const char **msgs = opts->msgs;
	const char *msg;

	if (!strcmp(cmd, "checkout"))
		msg = advice_commit_before_merge
		      ? _("Your local changes to the following files would be overwritten by checkout:\n%%s"
			  "Please commit your changes or stash them before you switch branches.")
		      : _("Your local changes to the following files would be overwritten by checkout:\n%%s");
	else if (!strcmp(cmd, "merge"))
		msg = advice_commit_before_merge
		      ? _("Your local changes to the following files would be overwritten by merge:\n%%s"
			  "Please commit your changes or stash them before you merge.")
		      : _("Your local changes to the following files would be overwritten by merge:\n%%s");
	else
		msg = advice_commit_before_merge
		      ? _("Your local changes to the following files would be overwritten by %s:\n%%s"
			  "Please commit your changes or stash them before you %s.")
		      : _("Your local changes to the following files would be overwritten by %s:\n%%s");
	msgs[ERROR_WOULD_OVERWRITE] = msgs[ERROR_NOT_UPTODATE_FILE] =
		xstrfmt(msg, cmd, cmd);

	msgs[ERROR_NOT_UPTODATE_DIR] =
		_("Updating the following directories would lose untracked files in them:\n%s");

	if (!strcmp(cmd, "checkout"))
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be removed by checkout:\n%%s"
			  "Please move or remove them before you switch branches.")
		      : _("The following untracked working tree files would be removed by checkout:\n%%s");
	else if (!strcmp(cmd, "merge"))
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be removed by merge:\n%%s"
			  "Please move or remove them before you merge.")
		      : _("The following untracked working tree files would be removed by merge:\n%%s");
	else
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be removed by %s:\n%%s"
			  "Please move or remove them before you %s.")
		      : _("The following untracked working tree files would be removed by %s:\n%%s");
	msgs[ERROR_WOULD_LOSE_UNTRACKED_REMOVED] = xstrfmt(msg, cmd, cmd);

	if (!strcmp(cmd, "checkout"))
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be overwritten by checkout:\n%%s"
			  "Please move or remove them before you switch branches.")
		      : _("The following untracked working tree files would be overwritten by checkout:\n%%s");
	else if (!strcmp(cmd, "merge"))
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be overwritten by merge:\n%%s"
			  "Please move or remove them before you merge.")
		      : _("The following untracked working tree files would be overwritten by merge:\n%%s");
	else
		msg = advice_commit_before_merge
		      ? _("The following untracked working tree files would be overwritten by %s:\n%%s"
			  "Please move or remove them before you %s.")
		      : _("The following untracked working tree files would be overwritten by %s:\n%%s");
	msgs[ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN] = xstrfmt(msg, cmd, cmd);

	/*
	 * Special case: ERROR_BIND_OVERLAP refers to a pair of paths, we
	 * cannot easily display it as a list.
	 */
	msgs[ERROR_BIND_OVERLAP] = _("Entry '%s' overlaps with '%s'.  Cannot bind.");

	msgs[ERROR_SPARSE_NOT_UPTODATE_FILE] =
		_("Cannot update sparse checkout: the following entries are not up-to-date:\n%s");
	msgs[ERROR_WOULD_LOSE_ORPHANED_OVERWRITTEN] =
		_("The following working tree files would be overwritten by sparse checkout update:\n%s");
	msgs[ERROR_WOULD_LOSE_ORPHANED_REMOVED] =
		_("The following working tree files would be removed by sparse checkout update:\n%s");
	msgs[ERROR_WOULD_LOSE_SUBMODULE] =
		_("Cannot update submodule:\n%s");

	opts->show_all_errors = 1;
	/* rejected paths may not have a static buffer */
	for (i = 0; i < ARRAY_SIZE(opts->unpack_rejects); i++)
		opts->unpack_rejects[i].strdup_strings = 1;
}