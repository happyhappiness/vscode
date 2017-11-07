int is_builtin(const char *s)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		struct cmd_struct *p = commands+i;
		if (!strcmp(s, p->cmd))
			return 1;
	}
	return 0;
}