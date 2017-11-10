static inline unsigned int canon_mode(unsigned int mode)
{
	if (S_ISREG(mode))
		return S_IFREG | ce_permissions(mode);
	if (S_ISLNK(mode))
		return S_IFLNK;
	if (S_ISDIR(mode))
		return S_IFDIR;
	return S_IFGITLINK;
}