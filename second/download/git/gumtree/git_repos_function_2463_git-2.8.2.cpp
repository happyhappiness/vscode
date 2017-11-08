const char *real_path(const char *path)
{
	return real_path_internal(path, 1);
}