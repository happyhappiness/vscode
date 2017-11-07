int run_hook_ve(const char *const *env, const char *name, va_list args)
{
	struct child_process hook;
	struct argv_array argv = ARGV_ARRAY_INIT;
	const char *p;
	int ret;

	p = find_hook(name);
	if (!p)
		return 0;

	argv_array_push(&argv, p);

	while ((p = va_arg(args, const char *)))
		argv_array_push(&argv, p);

	memset(&hook, 0, sizeof(hook));
	hook.argv = argv.argv;
	hook.env = env;
	hook.no_stdin = 1;
	hook.stdout_to_stderr = 1;

	ret = run_command(&hook);
	argv_array_clear(&argv);
	return ret;
}