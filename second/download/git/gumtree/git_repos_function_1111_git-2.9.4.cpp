static void set_from_env(const char **var, const char *envname)
{
	const char *val = getenv(envname);
	if (val)
		*var = val;
}