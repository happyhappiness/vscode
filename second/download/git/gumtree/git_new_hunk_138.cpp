
		fprintf(stderr, "Sorry, I did not understand your answer. "
				"Please type 'y' or 'n'\n");
	}
}

int mingw_unlink(const char *pathname)
{
	int ret, tries = 0;
	wchar_t wpathname[MAX_PATH];
	if (xutftowcs_path(wpathname, pathname) < 0)
		return -1;

	/* read-only files cannot be removed */
	_wchmod(wpathname, 0666);
	while ((ret = _wunlink(wpathname)) == -1 && tries < ARRAY_SIZE(delay)) {
		if (!is_file_in_use_error(GetLastError()))
			break;
		/*
		 * We assume that some other process had the source or
		 * destination file open at the wrong moment and retry.
		 * In order to give the other process a higher chance to
