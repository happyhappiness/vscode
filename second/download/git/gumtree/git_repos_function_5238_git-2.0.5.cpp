int mingw_unlink(const char *pathname)
{
	int ret, tries = 0;

	/* read-only files cannot be removed */
	chmod(pathname, 0666);
	while ((ret = unlink(pathname)) == -1 && tries < ARRAY_SIZE(delay)) {
		if (!is_file_in_use_error(GetLastError()))
			break;
		/*
		 * We assume that some other process had the source or
		 * destination file open at the wrong moment and retry.
		 * In order to give the other process a higher chance to
		 * complete its operation, we give up our time slice now.
		 * If we have to retry again, we do sleep a bit.
		 */
		Sleep(delay[tries]);
		tries++;
	}
	while (ret == -1 && is_file_in_use_error(GetLastError()) &&
	       ask_yes_no_if_possible("Unlink of file '%s' failed. "
			"Should I try again?", pathname))
	       ret = unlink(pathname);
	return ret;
}