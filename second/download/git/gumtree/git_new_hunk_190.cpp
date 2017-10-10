	N_("'git help -a' and 'git help -g' lists available subcommands and some\n"
	   "concept guides. See 'git help <command>' or 'git help <concept>'\n"
	   "to read about a specific subcommand or concept.");

static struct startup_info git_startup_info;
static int use_pager = -1;
static char orig_cwd[PATH_MAX];
static const char *env_names[] = {
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
	if (!getcwd(orig_cwd, sizeof(orig_cwd)))
		die_errno("cannot getcwd");
	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
		orig_env[i] = getenv(env_names[i]);
		if (orig_env[i])
			orig_env[i] = xstrdup(orig_env[i]);
	}
}

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

static void commit_pager_choice(void) {
	switch (use_pager) {
	case 0:
		setenv("GIT_PAGER", "cat", 1);
		break;
