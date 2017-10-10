static struct argv_array repack = ARGV_ARRAY_INIT;
static struct argv_array prune = ARGV_ARRAY_INIT;
static struct argv_array prune_worktrees = ARGV_ARRAY_INIT;
static struct argv_array rerere = ARGV_ARRAY_INIT;

static struct tempfile pidfile;

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

static void gc_config(void)
{
	const char *value;

	if (!git_config_get_value("gc.packrefs", &value)) {
		if (value && !strcmp(value, "notbare"))
