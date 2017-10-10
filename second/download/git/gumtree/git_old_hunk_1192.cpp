const char git_more_info_string[] =
	N_("'git help -a' and 'git help -g' list available subcommands and some\n"
	   "concept guides. See 'git help <command>' or 'git help <concept>'\n"
	   "to read about a specific subcommand or concept.");

static int use_pager = -1;
static char *orig_cwd;
static const char *env_names[] = {
	GIT_DIR_ENVIRONMENT,
	GIT_WORK_TREE_ENVIRONMENT,
	GIT_IMPLICIT_WORK_TREE_ENVIRONMENT,
	GIT_PREFIX_ENVIRONMENT
};
static char *orig_env[4];
static int save_restore_env_balance;

static void save_env_before_alias(void)
{
	int i;

	assert(save_restore_env_balance == 0);
	save_restore_env_balance = 1;
	orig_cwd = xgetcwd();
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		orig_env[i] = getenv(env_names[i]);
		orig_env[i] = xstrdup_or_null(orig_env[i]);
	}
}

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

static void commit_pager_choice(void) {
	switch (use_pager) {
	case 0:
		setenv("GIT_PAGER", "cat", 1);
		break;
