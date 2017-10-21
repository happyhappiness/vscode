static void set_env_num(const char *var, long num)
{
	char *mem;
	if (asprintf(&mem, "%s=%ld", var, num) < 0)
		out_of_memory("set_env_num");
	putenv(mem);
}