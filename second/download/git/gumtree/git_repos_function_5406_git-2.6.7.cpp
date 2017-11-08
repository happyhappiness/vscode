static int process_lstat_error(const char *path, int err)
{
	if (err == ENOENT || err == ENOTDIR)
		return remove_one_path(path);
	return error("lstat(\"%s\"): %s", path, strerror(errno));
}