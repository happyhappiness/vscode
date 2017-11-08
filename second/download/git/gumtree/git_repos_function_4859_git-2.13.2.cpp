static void show_info_page(const char *git_cmd)
{
	const char *page = cmd_to_page(git_cmd);
	setenv("INFOPATH", system_path(GIT_INFO_PATH), 1);
	execlp("info", "info", "gitman", page, (char *)NULL);
	die(_("no info viewer handled the request"));
}