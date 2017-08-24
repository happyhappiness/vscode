{
	/* Create the entry. */
	const wchar_t *linkname;
	wchar_t *fullname;
	mode_t final_mode, mode;
	int r;

	/* We identify hard/symlinks according to the link names. */
	/* Since link(2) and symlink(2) don't handle modes, we're done here. */
	linkname = archive_entry_hardlink_w(a->entry);
	if (linkname != NULL) {
		wchar_t *linkfull, *namefull;

		linkfull = __la_win_permissive_name_w(linkname);
		namefull = __la_win_permissive_name_w(a->name);
		if (linkfull == NULL || namefull == NULL) {
			errno = EINVAL;
			r = -1;
		} else {
			r = la_CreateHardLinkW(namefull, linkfull);
			if (r == 0) {
				la_dosmaperr(GetLastError());
				r = errno;
			} else
				r = 0;
		}
		/*
		 * New cpio and pax formats allow hardlink entries
		 * to carry data, so we may have to open the file
		 * for hardlink entries.
		 *
		 * If the hardlink was successfully created and
		 * the archive doesn't have carry data for it,
		 * consider it to be non-authoritative for meta data.
		 * This is consistent with GNU tar and BSD pax.
		 * If the hardlink does carry data, let the last
		 * archive entry decide ownership.
		 */
		if (r == 0 && a->filesize <= 0) {
			a->todo = 0;
			a->deferred = 0;
		} else if (r == 0 && a->filesize > 0) {
			a->fh = CreateFileW(namefull, GENERIC_WRITE, 0, NULL,
			    TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (a->fh == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				r = errno;
			}
		}
		free(linkfull);
		free(namefull);
		return (r);
	}
	linkname = archive_entry_symlink_w(a->entry);
	if (linkname != NULL) {
#if HAVE_SYMLINK
		return symlink(linkname, a->name) ? errno : 0;
#else
		return (EPERM);
#endif
	}

	/*
	 * The remaining system calls all set permissions, so let's
	 * try to take advantage of that to avoid an extra chmod()
	 * call.  (Recall that umask is set to zero right now!)
	 */

	/* Mode we want for the final restored object (w/o file type bits). */
	final_mode = a->mode & 07777;
	/*
	 * The mode that will actually be restored in this step.  Note
	 * that SUID, SGID, etc, require additional work to ensure
	 * security, so we never restore them at this point.
	 */
	mode = final_mode & 0777 & ~a->user_umask;

	switch (a->mode & AE_IFMT) {
	default:
		/* POSIX requires that we fall through here. */
		/* FALLTHROUGH */
	case AE_IFREG:
		fullname = a->name;
		/* O_WRONLY | O_CREAT | O_EXCL */
		a->fh = CreateFileW(fullname, GENERIC_WRITE, 0, NULL,
		    CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (a->fh == INVALID_HANDLE_VALUE &&
		    GetLastError() == ERROR_INVALID_NAME &&
		    fullname == a->name) {
			fullname = __la_win_permissive_name_w(a->name);
			a->fh = CreateFileW(fullname, GENERIC_WRITE, 0, NULL,
			    CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		if (a->fh == INVALID_HANDLE_VALUE) {
			if (GetLastError() == ERROR_ACCESS_DENIED) {
				DWORD attr;
				/* Simulate an errno of POSIX system. */
				attr = GetFileAttributesW(fullname);
				if (attr == (DWORD)-1)
					la_dosmaperr(GetLastError());
				else if (attr & FILE_ATTRIBUTE_DIRECTORY)
					errno = EISDIR;
				else
					errno = EACCES;
			} else
				la_dosmaperr(GetLastError());
			r = 1;
		} else
			r = 0;
		if (fullname != a->name)
			free(fullname);
		break;
	case AE_IFCHR:
	case AE_IFBLK:
		/* TODO: Find a better way to warn about our inability
		 * to restore a block device node. */
		return (EINVAL);
	case AE_IFDIR:
		mode = (mode | MINIMUM_DIR_MODE) & MAXIMUM_DIR_MODE;
		fullname = a->name;
		r = CreateDirectoryW(fullname, NULL);
		if (r == 0 && GetLastError() == ERROR_INVALID_NAME &&
			fullname == a->name) {
			fullname = __la_win_permissive_name_w(a->name);
			r = CreateDirectoryW(fullname, NULL);
		}
		if (r != 0) {
			r = 0;
			/* Defer setting dir times. */
			a->deferred |= (a->todo & TODO_TIMES);
			a->todo &= ~TODO_TIMES;
			/* Never use an immediate chmod(). */
			/* We can't avoid the chmod() entirely if EXTRACT_PERM
			 * because of SysV SGID inheritance. */
			if ((mode != final_mode)
			    || (a->flags & ARCHIVE_EXTRACT_PERM))
				a->deferred |= (a->todo & TODO_MODE);
			a->todo &= ~TODO_MODE;
		} else {
			la_dosmaperr(GetLastError());
			r = -1;
		}
		if (fullname != a->name)
			free(fullname);
		break;
	case AE_IFIFO:
		/* TODO: Find a better way to warn about our inability
		 * to restore a fifo. */
		return (EINVAL);
	}

	/* All the system calls above set errno on failure. */
	if (r)
		return (errno);

	/* If we managed to set the final mode, we've avoided a chmod(). */
	if (mode == final_mode)
		a->todo &= ~TODO_MODE;
	return (0);
}