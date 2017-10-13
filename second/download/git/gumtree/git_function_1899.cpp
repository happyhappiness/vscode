static void xmkdir(const char *path)
{
	path = get_mtime_path(path);
	if (mkdir(path, 0700))
		die_errno(_("failed to create directory %s"), path);
}