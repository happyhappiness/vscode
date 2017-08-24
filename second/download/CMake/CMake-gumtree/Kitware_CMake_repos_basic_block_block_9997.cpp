{
	HANDLE h;
	int r;
	DWORD flag = FILE_FLAG_BACKUP_SEMANTICS;
	
	if (sim_lstat && tree_current_is_physical_link(t))
		flag |= FILE_FLAG_OPEN_REPARSE_POINT;
	h = CreateFileW(tree_current_access_path(t), 0, FILE_SHARE_READ, NULL,
	    OPEN_EXISTING, flag, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		la_dosmaperr(GetLastError());
		t->tree_errno = errno;
		return (0);
	}
	r = GetFileInformationByHandle(h, st);
	CloseHandle(h);
	return (r);
}