
static int test_if_untracked_cache_is_supported(void)
{
	struct stat st;
	struct stat_data base;
	int fd, ret = 0;
	char *cwd;

	strbuf_addstr(&mtime_dir, "mtime-test-XXXXXX");
	if (!mkdtemp(mtime_dir.buf))
		die_errno("Could not make temporary directory");

	cwd = xgetcwd();
	fprintf(stderr, _("Testing mtime in '%s' "), cwd);
	free(cwd);

	atexit(remove_test_directory);
	xstat_mtime_dir(&st);
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
