static int remove_one_path(const char *path)
{
	if (!allow_remove)
		return error("%s: does not exist and --remove not passed", path);
	if (remove_file_from_cache(path))
		return error("%s: cannot remove from the index", path);
	return 0;
}