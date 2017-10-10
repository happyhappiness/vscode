
	if (fd < 0 && (oflags & O_ACCMODE) != O_RDONLY && errno == EACCES) {
		DWORD attrs = GetFileAttributesW(wfilename);
		if (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY))
			errno = EISDIR;
	}
	return fd;
}

static BOOL WINAPI ctrl_ignore(DWORD type)
{
	return TRUE;
