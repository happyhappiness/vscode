static void xunlink(const char *path)
{
	path = get_mtime_path(path);
	if (unlink(path))
		die_errno(_("failed to delete file %s"), path);
}