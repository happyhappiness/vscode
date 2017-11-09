void child_process_clear(struct child_process *child)
{
	argv_array_clear(&child->args);
	argv_array_clear(&child->env_array);
}