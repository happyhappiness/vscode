static inline int xutftowcs(wchar_t *wcs, const char *utf, size_t wcslen)
{
	return xutftowcsn(wcs, utf, wcslen, -1);
}