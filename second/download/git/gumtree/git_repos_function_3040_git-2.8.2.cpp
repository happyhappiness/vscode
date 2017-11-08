static inline int would_convert_to_git(const char *path)
{
	return convert_to_git(path, NULL, 0, NULL, 0);
}