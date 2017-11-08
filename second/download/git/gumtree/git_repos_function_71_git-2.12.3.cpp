static void add_cmd_list(struct cmdnames *cmds, struct cmdnames *old)
{
	int i;
	ALLOC_GROW(cmds->names, cmds->cnt + old->cnt, cmds->alloc);

	for (i = 0; i < old->cnt; i++)
		cmds->names[cmds->cnt++] = old->names[i];
	free(old->names);
	old->cnt = 0;
	old->names = NULL;
}