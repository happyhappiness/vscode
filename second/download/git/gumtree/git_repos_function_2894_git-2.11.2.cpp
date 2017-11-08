static int cmd2process_cmp(const struct cmd2process *e1,
			   const struct cmd2process *e2,
			   const void *unused)
{
	return strcmp(e1->cmd, e2->cmd);
}