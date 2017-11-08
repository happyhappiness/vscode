void prepare_pager_args(struct child_process *pager_process, const char *pager)
{
	argv_array_push(&pager_process->args, pager);
	pager_process->use_shell = 1;
	setup_pager_env(&pager_process->env_array);
}