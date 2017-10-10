	va_start(vp, fmt);
	vprintf(fmt, vp);
	putchar('\n');
	va_end(vp);
}

static void remove_test_directory(void)
{
	if (mtime_dir.len)
		remove_dir_recursively(&mtime_dir, 0);
}

static const char *get_mtime_path(const char *path)
{
	static struct strbuf sb = STRBUF_INIT;
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/%s", mtime_dir.buf, path);
	return sb.buf;
}

static void xmkdir(const char *path)
{
	path = get_mtime_path(path);
	if (mkdir(path, 0700))
		die_errno(_("failed to create directory %s"), path);
}

static int xstat_mtime_dir(struct stat *st)
{
	if (stat(mtime_dir.buf, st))
		die_errno(_("failed to stat %s"), mtime_dir.buf);
	return 0;
}

static int create_file(const char *path)
{
	int fd;
	path = get_mtime_path(path);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		die_errno(_("failed to create file %s"), path);
	return fd;
}

static void xunlink(const char *path)
{
	path = get_mtime_path(path);
	if (unlink(path))
		die_errno(_("failed to delete file %s"), path);
}

static void xrmdir(const char *path)
{
	path = get_mtime_path(path);
	if (rmdir(path))
		die_errno(_("failed to delete directory %s"), path);
}

static void avoid_racy(void)
{
	/*
	 * not use if we could usleep(10) if USE_NSEC is defined. The
	 * field nsec could be there, but the OS could choose to
	 * ignore it?
	 */
	sleep(1);
}

static int test_if_untracked_cache_is_supported(void)
{
	struct stat st;
	struct stat_data base;
	int fd, ret = 0;

	strbuf_addstr(&mtime_dir, "mtime-test-XXXXXX");
	if (!mkdtemp(mtime_dir.buf))
		die_errno("Could not make temporary directory");

	fprintf(stderr, _("Testing "));
	atexit(remove_test_directory);
	xstat_mtime_dir(&st);
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	fd = create_file("newfile");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		close(fd);
		fputc('\n', stderr);
		fprintf_ln(stderr,_("directory stat info does not "
				    "change after adding a new file"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	xmkdir("new-dir");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		close(fd);
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not change "
				     "after adding a new directory"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	write_or_die(fd, "data", 4);
	close(fd);
	xstat_mtime_dir(&st);
	if (match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info changes "
				     "after updating a file"));
		goto done;
	}
	fputc('.', stderr);

	avoid_racy();
	close(create_file("new-dir/new"));
	xstat_mtime_dir(&st);
	if (match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info changes after "
				     "adding a file inside subdirectory"));
		goto done;
	}
	fputc('.', stderr);

	avoid_racy();
	xunlink("newfile");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not "
				     "change after deleting a file"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	xunlink("new-dir/new");
	xrmdir("new-dir");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not "
				     "change after deleting a directory"));
		goto done;
	}

	if (rmdir(mtime_dir.buf))
		die_errno(_("failed to delete directory %s"), mtime_dir.buf);
	fprintf_ln(stderr, _(" OK"));
	ret = 1;

done:
	strbuf_release(&mtime_dir);
	return ret;
}

static int mark_ce_flags(const char *path, int flag, int mark)
{
	int namelen = strlen(path);
	int pos = cache_name_pos(path, namelen);
	if (0 <= pos) {
		if (mark)
