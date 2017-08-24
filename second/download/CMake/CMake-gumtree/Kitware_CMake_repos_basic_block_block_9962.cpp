{
	HANDLE handle;
	int r = 0;

	if (h == INVALID_HANDLE_VALUE && AE_IFLNK == rt->filetype)
		return (0);

	/* Close a file descriptor.
	 * It will not be used for SetFileTime() because it has been opened
	 * by a read only mode.
	 */
	if (h != INVALID_HANDLE_VALUE)
		CloseHandle(h);
	if ((t->flags & needsRestoreTimes) == 0)
		return (r);

	handle = CreateFileW(rt->full_path, FILE_WRITE_ATTRIBUTES,
		    0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		errno = EINVAL;
		return (-1);
	}

	if (SetFileTime(handle, NULL, &rt->lastAccessTime,
	    &rt->lastWriteTime) == 0) {
		errno = EINVAL;
		r = -1;
	} else
		r = 0;
	CloseHandle(handle);
	return (r);
}