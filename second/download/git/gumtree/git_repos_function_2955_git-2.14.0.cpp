static int error_dirty_index(struct replay_opts *opts)
{
	if (read_cache_unmerged())
		return error_resolve_conflict(_(action_name(opts)));

	error(_("your local changes would be overwritten by %s."),
		_(action_name(opts)));

	if (advice_commit_before_merge)
		advise(_("commit your changes or stash them to proceed."));
	return -1;
}