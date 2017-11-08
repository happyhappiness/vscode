int mingw_open (const char *filename, int oflags, ...)
{
	va_list args;
	unsigned mode;
	int fd;
	wchar_t wfilename[MAX_PATH];

	va_start(args, oflags);
	mode = va_arg(args, int);
	va_end(args);

	if (filename && !strcmp(filename, "/dev/null"))
		filename = "nul";

	if (xutftowcs_path(wfilename, filename) < 0)
		return -1;
	fd = _wopen(wfilename, oflags, mode);

	if (fd < 0 && (oflags & O_ACCMODE) != O_RDONLY && errno == EACCES) {
		DWORD attrs = GetFileAttributesW(wfilename);
		if (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY))
			errno = EISDIR;
	}
	return fd;
}