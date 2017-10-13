static int error_dirty_index(struct replay_opts *opts)
{
	if (read_cache_unmerged())
		return error_resolve_conflict(action_name(opts));

	/* Different translation strings for cherry-pick and revert */
	if (opts->action == REPLAY_PICK)
		error(_("Your local changes would be overwritten by cherry-pick."));
	else
		error(_("Your local changes would be overwritten by revert."));

	if (advice_commit_before_merge)
		advise(_("Commit your changes or stash them to proceed."));
	return -1;
}