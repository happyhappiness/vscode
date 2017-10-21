static void set_env_str(const char *var, const char *str)
{
#ifdef HAVE_PUTENV
	char *mem;
	if (asprintf(&mem, "%s=%s", var, str) < 0)
		out_of_memory("set_env_str");
	putenv(mem);
#endif
}