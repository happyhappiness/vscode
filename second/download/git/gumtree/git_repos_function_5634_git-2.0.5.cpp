int closedir(DIR *dir)
{
	if (!dir) {
		errno = EBADF;
		return -1;
	}

	if (dir->dd_handle != INVALID_HANDLE_VALUE)
		FindClose(dir->dd_handle);
	free(dir);
	return 0;
}