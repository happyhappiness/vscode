static int is_noop(const enum todo_command command)
{
	return TODO_NOOP <= command;
}