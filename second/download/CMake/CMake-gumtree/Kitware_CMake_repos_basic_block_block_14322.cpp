{
	wchar_t *w;
	size_t path_length;

	if (wp == NULL)
		return(0);
	if (wcschr(wp, L'\\') == NULL)
		return(0);
	path_length = wcslen(wp);
	if (archive_wstring_ensure(ws, path_length) == NULL)
		return(-1);
	archive_wstrncpy(ws, wp, path_length);
	for (w = ws->s; *w; w++) {
		if (*w == L'\\')
			*w = L'/';
	}
	return(1);
}