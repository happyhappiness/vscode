static int do_lstat(int follow, const char *file_name, struct stat *buf)
{
	int err;
	WIN32_FILE_ATTRIBUTE_DATA fdata;

	if (!(err = get_file_attr(file_name, &fdata))) {
		buf->st_ino = 0;
		buf->st_gid = 0;
		buf->st_uid = 0;
		buf->st_nlink = 1;
		buf->st_mode = file_attr_to_st_mode(fdata.dwFileAttributes);
		buf->st_size = fdata.nFileSizeLow |
			(((off_t)fdata.nFileSizeHigh)<<32);
		buf->st_dev = buf->st_rdev = 0; /* not used by Git */
		buf->st_atime = filetime_to_time_t(&(fdata.ftLastAccessTime));
		buf->st_mtime = filetime_to_time_t(&(fdata.ftLastWriteTime));
		buf->st_ctime = filetime_to_time_t(&(fdata.ftCreationTime));
		if (fdata.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
			WIN32_FIND_DATAA findbuf;
			HANDLE handle = FindFirstFileA(file_name, &findbuf);
			if (handle != INVALID_HANDLE_VALUE) {
				if ((findbuf.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) &&
						(findbuf.dwReserved0 == IO_REPARSE_TAG_SYMLINK)) {
					if (follow) {
						char buffer[MAXIMUM_REPARSE_DATA_BUFFER_SIZE];
						buf->st_size = readlink(file_name, buffer, MAXIMUM_REPARSE_DATA_BUFFER_SIZE);
					} else {
						buf->st_mode = S_IFLNK;
					}
					buf->st_mode |= S_IREAD;
					if (!(findbuf.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
						buf->st_mode |= S_IWRITE;
				}
				FindClose(handle);
			}
		}
		return 0;
	}
	errno = err;
	return -1;
}