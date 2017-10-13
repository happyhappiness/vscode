static void restore_env(int external_alias)
{
	int i;

	assert(save_restore_env_balance == 1);
	save_restore_env_balance = 0;
	if (!external_alias && orig_cwd && chdir(orig_cwd))
		die_errno("could not move to %s", orig_cwd);
	free(orig_cwd);
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		if (external_alias &&
		    !strcmp(env_names[i], GIT_PREFIX_ENVIRONMENT))
			continue;
		if (orig_env[i]) {
			setenv(env_names[i], orig_env[i], 1);
			free(orig_env[i]);
		} else {
			unsetenv(env_names[i]);
		}
	}
}