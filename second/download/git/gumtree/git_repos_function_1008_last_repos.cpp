int run_hook_ve(const char *const *env, const char *name, va_list args)
{
	struct child_process hook = CHILD_PROCESS_INIT;
	const char *p;

	p = find_hook(name);
	if (!p)
		return 0;

	argv_array_push(&hook.args, p);
	while ((p = va_arg(args, const char *)))
		argv_array_push(&hook.args, p);
	hook.env = env;
	hook.no_stdin = 1;
	hook.stdout_to_stderr = 1;

	return run_command(&hook);
}