static const char *command_to_string(const enum todo_command command)
{
	if ((size_t)command < ARRAY_SIZE(todo_command_strings))
		return todo_command_strings[command];
	die("Unknown command: %d", command);
}