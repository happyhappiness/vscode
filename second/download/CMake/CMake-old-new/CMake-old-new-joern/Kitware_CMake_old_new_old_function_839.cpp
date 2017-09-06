int
archive_read_disk_entry_from_file(struct archive *_a,
    struct archive_entry *entry, int fd, const struct stat *st)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	const wchar_t *path;
	const wchar_t *wname;
	const char *name;
	HANDLE h;
	BY_HANDLE_FILE_INFORMATION bhfi;
	DWORD fileAttributes = 0;
	int r;

	archive_clear_error(_a);
	wname = archive_entry_sourcepath_w(entry);
	if (wname == NULL)
		wname = archive_entry_pathname_w(entry);
	if (wname == NULL) {
		archive_set_error(&a->archive, EINVAL,
		    "Can't get a wide character version of the path");
		return (ARCHIVE_FAILED);
	}
	path = __la_win_permissive_name_w(wname);

	if (st == NULL) {
		/*
		 * Get metadata through GetFileInformationByHandle().
		 */
		if (fd >= 0) {
			h = (HANDLE)_get_osfhandle(fd);
			r = GetFileInformationByHandle(h, &bhfi);
			if (r == 0) {
				archive_set_error(&a->archive, GetLastError(),
				    "Can't GetFileInformationByHandle");
				return (ARCHIVE_FAILED);
			}
			entry_copy_bhfi(entry, path, NULL, &bhfi);
		} else {
			WIN32_FIND_DATAW findData;
			DWORD flag, desiredAccess;
	
			h = FindFirstFileW(path, &findData);
			if (h == INVALID_DIR_HANDLE) {
				archive_set_error(&a->archive, GetLastError(),
				    "Can't FindFirstFileW");
				return (ARCHIVE_FAILED);
			}
			FindClose(h);

			flag = FILE_FLAG_BACKUP_SEMANTICS;
			if (!a->follow_symlinks &&
			    (findData.dwFileAttributes
			      & FILE_ATTRIBUTE_REPARSE_POINT) &&
				  (findData.dwReserved0 == IO_REPARSE_TAG_SYMLINK)) {
				flag |= FILE_FLAG_OPEN_REPARSE_POINT;
				desiredAccess = 0;
			} else if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				desiredAccess = 0;
			} else
				desiredAccess = GENERIC_READ;

			h = CreateFileW(path, desiredAccess, 0, NULL,
			    OPEN_EXISTING, flag, NULL);
			if (h == INVALID_HANDLE_VALUE) {
				archive_set_error(&a->archive,
				    GetLastError(),
				    "Can't CreateFileW");
				return (ARCHIVE_FAILED);
			}
			r = GetFileInformationByHandle(h, &bhfi);
			if (r == 0) {
				archive_set_error(&a->archive,
				    GetLastError(),
				    "Can't GetFileInformationByHandle");
				CloseHandle(h);
				return (ARCHIVE_FAILED);
			}
			entry_copy_bhfi(entry, path, &findData, &bhfi);
		}
		fileAttributes = bhfi.dwFileAttributes;
	} else {
		archive_entry_copy_stat(entry, st);
		h = INVALID_DIR_HANDLE;
	}

	/* Lookup uname/gname */
	name = archive_read_disk_uname(_a, archive_entry_uid(entry));
	if (name != NULL)
		archive_entry_copy_uname(entry, name);
	name = archive_read_disk_gname(_a, archive_entry_gid(entry));
	if (name != NULL)
		archive_entry_copy_gname(entry, name);

	/*
	 * Can this file be sparse file ?
	 */
	if (archive_entry_filetype(entry) != AE_IFREG
	    || archive_entry_size(entry) <= 0
		|| archive_entry_hardlink(entry) != NULL) {
		if (h != INVALID_HANDLE_VALUE && fd < 0)
			CloseHandle(h);
		return (ARCHIVE_OK);
	}

	if (h == INVALID_HANDLE_VALUE) {
		if (fd >= 0) {
			h = (HANDLE)_get_osfhandle(fd);
		} else {
			h = CreateFileW(path, GENERIC_READ, 0, NULL,
			    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
			if (h == INVALID_HANDLE_VALUE) {
				archive_set_error(&a->archive, GetLastError(),
				    "Can't CreateFileW");
				return (ARCHIVE_FAILED);
			}
		}
		r = GetFileInformationByHandle(h, &bhfi);
		if (r == 0) {
			archive_set_error(&a->archive, GetLastError(),
			    "Can't GetFileInformationByHandle");
			if (h != INVALID_HANDLE_VALUE && fd < 0)
				CloseHandle(h);
			return (ARCHIVE_FAILED);
		}
		fileAttributes = bhfi.dwFileAttributes;
	}

	/* Sparse file must be set a mark, FILE_ATTRIBUTE_SPARSE_FILE */
	if ((fileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) == 0) {
		if (fd < 0)
			CloseHandle(h);
		return (ARCHIVE_OK);
	}

	r = setup_sparse_from_disk(a, entry, h);
	if (fd < 0)
		CloseHandle(h);

	return (r);
}