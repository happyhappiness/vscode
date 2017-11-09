static void read_branches(void)
{
	if (branch_list.nr)
		return;
	git_config(config_read_branches, NULL);
}