char *mingw_getcwd(char *pointer, int len)
{
	int i;
	wchar_t wpointer[MAX_PATH];
	if (!_wgetcwd(wpointer, ARRAY_SIZE(wpointer)))
		return NULL;
	if (xwcstoutf(pointer, wpointer, len) < 0)
		return NULL;
	for (i = 0; pointer[i]; i++)
		if (pointer[i] == '\\')
			pointer[i] = '/';
	return pointer;
}