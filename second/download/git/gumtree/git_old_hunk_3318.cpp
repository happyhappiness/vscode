	return ch;
}

#undef fopen
FILE *mingw_fopen (const char *filename, const char *otype)
{
	FILE *file;
	wchar_t wfilename[MAX_PATH], wotype[4];
	if (filename && !strcmp(filename, "/dev/null"))
		filename = "nul";
	if (xutftowcs_path(wfilename, filename) < 0 ||
		xutftowcs(wotype, otype, ARRAY_SIZE(wotype)) < 0)
		return NULL;
	file = _wfopen(wfilename, wotype);
	return file;
}

FILE *mingw_freopen (const char *filename, const char *otype, FILE *stream)
{
	FILE *file;
	wchar_t wfilename[MAX_PATH], wotype[4];
	if (filename && !strcmp(filename, "/dev/null"))
		filename = "nul";
	if (xutftowcs_path(wfilename, filename) < 0 ||
		xutftowcs(wotype, otype, ARRAY_SIZE(wotype)) < 0)
		return NULL;
	file = _wfreopen(wfilename, wotype, stream);
	return file;
}

#undef fflush
int mingw_fflush(FILE *stream)
{
