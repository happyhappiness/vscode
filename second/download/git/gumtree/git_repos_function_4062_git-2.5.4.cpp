static void open_html(const char *path)
{
	execl_git_cmd("web--browse", "-c", "help.browser", path, (char *)NULL);
}