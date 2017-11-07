static inline int mingw_mkdir(const char *path, int mode)
{
	return mkdir(path);
}