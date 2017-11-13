static const char *check_git_cmd(const char* cmd)
{
	char *alias;

	if (is_git_command(cmd))
		return cmd;

	alias = alias_lookup(cmd);
	if (alias) {
		printf_ln(_("`git %s' is aliased to `%s'"), cmd, alias);
		free(alias);
		exit(0);
	}

	if (exclude_guides)
		return help_unknown_cmd(cmd);

	return cmd;
}