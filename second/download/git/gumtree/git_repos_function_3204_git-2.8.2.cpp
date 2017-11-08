void prepare_pager_args(struct child_process *pager_process, const char *pager)
{
	argv_array_push(&pager_process->args, pager);
	pager_process->use_shell = 1;
	if (!getenv("LESS"))
		argv_array_push(&pager_process->env_array, "LESS=FRX");
	if (!getenv("LV"))
		argv_array_push(&pager_process->env_array, "LV=-c");
}