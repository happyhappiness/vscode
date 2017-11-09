static int is_fixup(enum todo_command command)
{
	return command == TODO_FIXUP || command == TODO_SQUASH;
}