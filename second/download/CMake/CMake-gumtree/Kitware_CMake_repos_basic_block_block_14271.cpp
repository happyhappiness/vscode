{
	wchar_t *wpath;
	HANDLE handle;

	handle = CreateFileA(path, dwDesiredAccess, dwShareMode,
	    lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
	    hTemplateFile);
	if (handle != INVALID_HANDLE_VALUE)
		return (handle);
	if (GetLastError() != ERROR_PATH_NOT_FOUND)
		return (handle);
	wpath = __la_win_permissive_name(path);
	if (wpath == NULL)
		return (handle);
	handle = CreateFileW(wpath, dwDesiredAccess, dwShareMode,
	    lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
	    hTemplateFile);
	free(wpath);
	return (handle);
}