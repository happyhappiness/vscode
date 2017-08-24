((st->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) &&
	    findData.dwReserved0 == IO_REPARSE_TAG_SYMLINK)
		*mode |= S_IFLNK;
	else if (st->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		*mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
	else {
		const wchar_t *p;

		*mode |= S_IFREG;
		p = wcsrchr(path, L'.');
		if (p != NULL && wcslen(p) == 4) {
			switch (p[1]) {
			case L'B': case L'b':
				if ((p[2] == L'A' || p[2] == L'a' ) &&
				    (p[3] == L'T' || p[3] == L't' ))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			case L'C': case L'c':
				if (((p[2] == L'M' || p[2] == L'm' ) &&
				    (p[3] == L'D' || p[3] == L'd' )))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			case L'E': case L'e':
				if ((p[2] == L'X' || p[2] == L'x' ) &&
				    (p[3] == L'E' || p[3] == L'e' ))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			default:
				break;
			}
		}
	}