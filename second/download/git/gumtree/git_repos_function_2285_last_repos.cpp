static inline int directory_size(const char *filename)
{
	const char *s = strrchr(filename, '/');
	if (!s)
		return 0;
	return s - filename + 1;
}