static void list_builtins(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(commands); i++)
		printf("%s\n", commands[i].cmd);
}