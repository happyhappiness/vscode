static int process_lstat_error(const char *path, int err)
{
	if (is_missing_file_error(err))
		return remove_one_path(path);
	return error("lstat(\"%s\"): %s", path, strerror(err));
}