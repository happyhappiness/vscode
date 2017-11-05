static inline int xutftowcs_path(wchar_t *wcs, const char *utf)
{
	int result = xutftowcsn(wcs, utf, MAX_PATH, -1);
	if (result < 0 && errno == ERANGE)
		errno = ENAMETOOLONG;
	return result;
}