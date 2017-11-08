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