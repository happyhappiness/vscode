static char *envdup(const char *var)
{
	const char *val = getenv(var);
	return val ? xstrdup(val) : NULL;
}