static void dissociate_from_references(void)
{
	static const char* argv[] = { "repack", "-a", "-d", NULL };

	if (run_command_v_opt(argv, RUN_GIT_CMD|RUN_COMMAND_NO_STDIN))
		die(_("cannot repack to clean up"));
	if (unlink(git_path("objects/info/alternates")) && errno != ENOENT)
		die_errno(_("cannot unlink temporary alternates file"));
}