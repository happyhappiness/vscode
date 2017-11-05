static void restore_env(void)
{
	int i;
	if (*orig_cwd && chdir(orig_cwd))
		die_errno("could not move to %s", orig_cwd);
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		if (orig_env[i])
			setenv(env_names[i], orig_env[i], 1);
		else
			unsetenv(env_names[i]);
	}
}