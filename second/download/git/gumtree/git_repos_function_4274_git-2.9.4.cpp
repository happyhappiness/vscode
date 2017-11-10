static const char *cmd_to_page(const char *git_cmd)
{
	if (!git_cmd)
		return "git";
	else if (starts_with(git_cmd, "git"))
		return git_cmd;
	else if (is_git_command(git_cmd))
		return xstrfmt("git-%s", git_cmd);
	else
		return xstrfmt("git%s", git_cmd);
}