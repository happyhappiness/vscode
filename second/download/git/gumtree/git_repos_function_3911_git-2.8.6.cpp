static void save_env_before_alias(void)
{
	int i;

	assert(save_restore_env_balance == 0);
	save_restore_env_balance = 1;
	orig_cwd = xgetcwd();
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		orig_env[i] = getenv(env_names[i]);
		if (orig_env[i])
			orig_env[i] = xstrdup(orig_env[i]);
	}
}