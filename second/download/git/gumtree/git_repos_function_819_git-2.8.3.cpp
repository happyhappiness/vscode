static int execv_shell_cmd(const char **argv)
{
	struct argv_array nargv = ARGV_ARRAY_INIT;
	prepare_shell_cmd(&nargv, argv);
	trace_argv_printf(nargv.argv, "trace: exec:");
	sane_execvp(nargv.argv[0], (char **)nargv.argv);
	argv_array_clear(&nargv);
	return -1;
}