{
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