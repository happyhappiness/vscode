	GIT_DIR_ENVIRONMENT,
	GIT_WORK_TREE_ENVIRONMENT,
	GIT_IMPLICIT_WORK_TREE_ENVIRONMENT,
	GIT_PREFIX_ENVIRONMENT
};
static char *orig_env[4];
static int saved_environment;

static void save_env(void)
{
	int i;
	if (saved_environment)
		return;
	saved_environment = 1;
	orig_cwd = xgetcwd();
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		orig_env[i] = getenv(env_names[i]);
		if (orig_env[i])
			orig_env[i] = xstrdup(orig_env[i]);
	}
}

static void restore_env(void)
{
	int i;
	if (orig_cwd && chdir(orig_cwd))
		die_errno("could not move to %s", orig_cwd);
	free(orig_cwd);
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		if (orig_env[i])
			setenv(env_names[i], orig_env[i], 1);
		else
			unsetenv(env_names[i]);
	}
}

static void commit_pager_choice(void) {
	switch (use_pager) {
	case 0:
