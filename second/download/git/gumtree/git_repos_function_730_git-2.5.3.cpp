static inline unsigned int create_ce_mode(unsigned int mode)
{
	if (S_ISLNK(mode))
		return S_IFLNK;
	if (S_ISDIR(mode) || S_ISGITLINK(mode))
		return S_IFGITLINK;
	return S_IFREG | ce_permissions(mode);
}