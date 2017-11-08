static const char *command_to_string(const enum todo_command command)
{
	if (command < TODO_COMMENT)
		return todo_command_info[command].str;
	die("Unknown command: %d", command);
}