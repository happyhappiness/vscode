static void NORETURN daemon_die(const char *err, va_list params)
{
	logreport(LOG_ERR, err, params);
	exit(1);
}

static const char *path_ok(const char *directory)
{
	static char rpath[PATH_MAX];
	static char interp_path[PATH_MAX];
	const char *path;
	const char *dir;

	dir = directory;

	if (daemon_avoid_alias(dir)) {
		logerror("'%s': aliased", dir);
		return NULL;
