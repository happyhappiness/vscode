int check_pager_config(const char *cmd)
{
	struct pager_config c;
	c.cmd = cmd;
	c.want = -1;
	c.value = NULL;
	git_config(pager_command_config, &c);
	if (c.value)
		pager_program = c.value;
	return c.want;
}