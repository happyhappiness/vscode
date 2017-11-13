static void save_env(void)
{
	int i;
	if (saved_environment)
		return;
	saved_environment = 1;
	if (!getcwd(orig_cwd, sizeof(orig_cwd)))
		die_errno("cannot getcwd");
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		orig_env[i] = getenv(env_names[i]);
		if (orig_env[i])
			orig_env[i] = xstrdup(orig_env[i]);
	}
}