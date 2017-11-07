static int xstat_mtime_dir(struct stat *st)
{
	if (stat(mtime_dir.buf, st))
		die_errno(_("failed to stat %s"), mtime_dir.buf);
	return 0;
}