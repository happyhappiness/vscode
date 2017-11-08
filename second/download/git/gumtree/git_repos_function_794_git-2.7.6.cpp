void child_process_init(struct child_process *child)
{
	memset(child, 0, sizeof(*child));
	argv_array_init(&child->args);
	argv_array_init(&child->env_array);
}