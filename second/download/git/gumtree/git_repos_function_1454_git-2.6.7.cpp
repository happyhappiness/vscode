static inline char *git_find_last_dir_sep(const char *path)
{
	return strrchr(path, '/');
}