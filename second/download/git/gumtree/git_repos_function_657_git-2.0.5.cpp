int run_hook_le(const char *const *env, const char *name, ...)
{
	va_list args;
	int ret;

	va_start(args, name);
	ret = run_hook_ve(env, name, args);
	va_end(args);

	return ret;
}