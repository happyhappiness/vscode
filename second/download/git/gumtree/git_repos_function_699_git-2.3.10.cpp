static int execv_shell_cmd(const char **argv)
{
	const char **nargv = prepare_shell_cmd(argv);
	trace_argv_printf(nargv, "trace: exec:");
	sane_execvp(nargv[0], (char **)nargv);
	free(nargv);
	return -1;
}