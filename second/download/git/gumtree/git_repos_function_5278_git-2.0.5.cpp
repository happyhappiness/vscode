static char **copy_environ(void)
{
	char **env;
	int i = 0;
	while (environ[i])
		i++;
	env = xmalloc((i+1)*sizeof(*env));
	for (i = 0; environ[i]; i++)
		env[i] = xstrdup(environ[i]);
	env[i] = NULL;
	return env;
}