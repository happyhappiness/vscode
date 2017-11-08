int run_commit_hook(int editor_is_used, const char *index_file, const char *name, ...)
{
	struct argv_array hook_env = ARGV_ARRAY_INIT;
	va_list args;
	int ret;

	argv_array_pushf(&hook_env, "GIT_INDEX_FILE=%s", index_file);

	/*
	 * Let the hook know that no editor will be launched.
	 */
	if (!editor_is_used)
		argv_array_push(&hook_env, "GIT_EDITOR=:");

	va_start(args, name);
	ret = run_hook_ve(hook_env.argv,name, args);
	va_end(args);
	argv_array_clear(&hook_env);

	return ret;
}