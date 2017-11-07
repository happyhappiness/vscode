static char *getenv_cs(const char *name)
{
	size_t len = strlen(name);
	int i = lookup_env(environ, name, len);
	if (i >= 0)
		return environ[i] + len + 1;	/* skip past name and '=' */
	return getenv(name);
}