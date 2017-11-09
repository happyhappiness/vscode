static inline char *mingw_find_last_dir_sep(const char *path)
{
	char *ret = NULL;
	for (; *path; ++path)
		if (is_dir_sep(*path))
			ret = (char *)path;
	return ret;
}