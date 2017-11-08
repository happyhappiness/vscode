static int is_git_command(const char *s)
{
	if (is_builtin(s))
		return 1;

	load_command_list("git-", &main_cmds, &other_cmds);
	return is_in_cmdlist(&main_cmds, s) ||
		is_in_cmdlist(&other_cmds, s);
}