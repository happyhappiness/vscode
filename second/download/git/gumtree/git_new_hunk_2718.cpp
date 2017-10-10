static struct argv_array repack = ARGV_ARRAY_INIT;
static struct argv_array prune = ARGV_ARRAY_INIT;
static struct argv_array prune_worktrees = ARGV_ARRAY_INIT;
static struct argv_array rerere = ARGV_ARRAY_INIT;

static struct tempfile pidfile;
static struct lock_file log_lock;

static void git_config_date_string(const char *key, const char **output)
{
	if (git_config_get_string_const(key, output))
		return;
	if (strcmp(*output, "now")) {
		unsigned long now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
}

static void process_log_file(void)
{
	struct stat st;
	if (!fstat(get_lock_file_fd(&log_lock), &st) && st.st_size)
		commit_lock_file(&log_lock);
	else
		rollback_lock_file(&log_lock);
}

static void process_log_file_at_exit(void)
{
	fflush(stderr);
	process_log_file();
}

static void process_log_file_on_signal(int signo)
{
	process_log_file();
	sigchain_pop(signo);
	raise(signo);
}

static void gc_config(void)
{
	const char *value;

	if (!git_config_get_value("gc.packrefs", &value)) {
		if (value && !strcmp(value, "notbare"))
