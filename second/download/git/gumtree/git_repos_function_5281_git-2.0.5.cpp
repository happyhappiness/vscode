static char **env_setenv(char **env, const char *name)
{
	char *eq = strchrnul(name, '=');
	int i = lookup_env(env, name, eq-name);

	if (i < 0) {
		if (*eq) {
			for (i = 0; env[i]; i++)
				;
			env = xrealloc(env, (i+2)*sizeof(*env));
			env[i] = xstrdup(name);
			env[i+1] = NULL;
		}
	}
	else {
		free(env[i]);
		if (*eq)
			env[i] = xstrdup(name);
		else
			for (; env[i]; i++)
				env[i] = env[i+1];
	}
	return env;
}