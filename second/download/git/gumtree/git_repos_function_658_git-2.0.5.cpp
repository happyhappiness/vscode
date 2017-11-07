int run_hook_with_custom_index(const char *index_file, const char *name, ...)
{
	const char *hook_env[3] =  { NULL };
	char index[PATH_MAX];
	va_list args;
	int ret;

	snprintf(index, sizeof(index), "GIT_INDEX_FILE=%s", index_file);
	hook_env[0] = index;

	va_start(args, name);
	ret = run_hook_ve(hook_env, name, args);
	va_end(args);

	return ret;
}