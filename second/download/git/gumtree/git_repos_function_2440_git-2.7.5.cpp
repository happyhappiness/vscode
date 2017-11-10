const char *real_path_if_valid(const char *path)
{
	return real_path_internal(path, 0);
}