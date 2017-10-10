	if (!*pager || !strcmp(pager, "cat"))
		pager = NULL;

	return pager;
}

void prepare_pager_args(struct child_process *pager_process, const char *pager)
{
	argv_array_push(&pager_process->args, pager);
	pager_process->use_shell = 1;
	if (!getenv("LESS"))
		argv_array_push(&pager_process->env_array, "LESS=FRX");
	if (!getenv("LV"))
		argv_array_push(&pager_process->env_array, "LV=-c");
}

void setup_pager(void)
{
	const char *pager = git_pager(isatty(1));

