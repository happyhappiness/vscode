char **make_augmented_environ(const char *const *vars)
{
	char **env = copy_environ();

	while (*vars)
		env = env_setenv(env, *vars++);
	return env;
}