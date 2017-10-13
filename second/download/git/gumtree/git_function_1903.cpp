static void xrmdir(const char *path)
{
	path = get_mtime_path(path);
	if (rmdir(path))
		die_errno(_("failed to delete directory %s"), path);
}