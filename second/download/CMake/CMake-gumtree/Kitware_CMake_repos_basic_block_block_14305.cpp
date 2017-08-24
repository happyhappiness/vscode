{
	BY_HANDLE_FILE_INFORMATION info;
	ULARGE_INTEGER ino64;
	DWORD ftype;
	mode_t mode;
	time_t t;
	long ns;

	switch (ftype = GetFileType(handle)) {
	case FILE_TYPE_UNKNOWN:
		errno = EBADF;
		return (-1);
	case FILE_TYPE_CHAR:
	case FILE_TYPE_PIPE:
		if (ftype == FILE_TYPE_CHAR) {
			st->st_mode = S_IFCHR;
			st->st_size = 0;
		} else {
			DWORD avail;

			st->st_mode = S_IFIFO;
			if (PeekNamedPipe(handle, NULL, 0, NULL, &avail, NULL))
				st->st_size = avail;
			else
				st->st_size = 0;
		}
		st->st_atime = 0;
		st->st_atime_nsec = 0;
		st->st_mtime = 0;
		st->st_mtime_nsec = 0;
		st->st_ctime = 0;
		st->st_ctime_nsec = 0;
		st->st_ino = 0;
		st->st_nlink = 1;
		st->st_uid = 0;
		st->st_gid = 0;
		st->st_rdev = 0;
		st->st_dev = 0;
		return (0);
	case FILE_TYPE_DISK:
		break;
	default:
		/* This ftype is undocumented type. */
		la_dosmaperr(GetLastError());
		return (-1);
	}

	ZeroMemory(&info, sizeof(info));
	if (!GetFileInformationByHandle (handle, &info)) {
		la_dosmaperr(GetLastError());
		return (-1);
	}

	mode = S_IRUSR | S_IRGRP | S_IROTH;
	if ((info.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == 0)
		mode |= S_IWUSR | S_IWGRP | S_IWOTH;
	if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
	else
		mode |= S_IFREG;
	st->st_mode = mode;

	fileTimeToUTC(&info.ftLastAccessTime, &t, &ns);
	st->st_atime = t;
	st->st_atime_nsec = ns;
	fileTimeToUTC(&info.ftLastWriteTime, &t, &ns);
	st->st_mtime = t;
	st->st_mtime_nsec = ns;
	fileTimeToUTC(&info.ftCreationTime, &t, &ns);
	st->st_ctime = t;
	st->st_ctime_nsec = ns;
	st->st_size =
	    ((int64_t)(info.nFileSizeHigh) * ((int64_t)MAXDWORD + 1))
		+ (int64_t)(info.nFileSizeLow);
#ifdef SIMULATE_WIN_STAT
	st->st_ino = 0;
	st->st_nlink = 1;
	st->st_dev = 0;
#else
	/* Getting FileIndex as i-node. We should remove a sequence which
	 * is high-16-bits of nFileIndexHigh. */
	ino64.HighPart = info.nFileIndexHigh & 0x0000FFFFUL;
	ino64.LowPart  = info.nFileIndexLow;
	st->st_ino = ino64.QuadPart;
	st->st_nlink = info.nNumberOfLinks;
	if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		++st->st_nlink;/* Add parent directory. */
	st->st_dev = info.dwVolumeSerialNumber;
#endif
	st->st_uid = 0;
	st->st_gid = 0;
	st->st_rdev = 0;
	return (0);
}