unsigned long git_env_ulong(const char *k, unsigned long val)
{
	const char *v = getenv(k);
	if (v && !git_parse_ulong(v, &val))
		die("failed to parse %s", k);
	return val;
}