static int continue_single_pick(void)
{
	const char *argv[] = { "commit", NULL };

	if (!file_exists(git_path("CHERRY_PICK_HEAD")) &&
	    !file_exists(git_path("REVERT_HEAD")))
		return error(_("no cherry-pick or revert in progress"));
	return run_command_v_opt(argv, RUN_GIT_CMD);
}