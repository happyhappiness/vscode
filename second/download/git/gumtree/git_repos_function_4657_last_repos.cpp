void setup_auto_pager(const char *cmd, int def)
{
	if (use_pager != -1 || pager_in_use())
		return;
	use_pager = check_pager_config(cmd);
	if (use_pager == -1)
		use_pager = def;
	commit_pager_choice();
}