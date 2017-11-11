int execl_git_cmd(const char *cmd,...)
{
	int argc;
	const char *argv[MAX_ARGS + 1];
	const char *arg;
	va_list param;

	va_start(param, cmd);
	argv[0] = cmd;
	argc = 1;
	while (argc < MAX_ARGS) {
		arg = argv[argc++] = va_arg(param, char *);
		if (!arg)
			break;
	}
	va_end(param);
	if (MAX_ARGS <= argc)
		return error("too many args to run %s", cmd);

	argv[argc] = NULL;
	return execv_git_cmd(argv);
}