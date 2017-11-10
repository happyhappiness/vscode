static void clean_cmdnames(struct cmdnames *cmds)
{
	int i;
	for (i = 0; i < cmds->cnt; ++i)
		free(cmds->names[i]);
	free(cmds->names);
	cmds->cnt = 0;
	cmds->alloc = 0;
}