static int
cleanup_pathname(struct archive_write_disk *a)
{
	wchar_t *dest, *src, *p, *top;
	wchar_t separator = L'\0';

	p = a->name;
	if (*p == L'\0') {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid empty pathname");
		return (ARCHIVE_FAILED);
	}

	/* Replace '/' by '\' */
	for (; *p != L'\0'; p++) {
		if (*p == L'/')
			*p = L'\\';
	}
	p = a->name;

	/* Skip leading "\\.\" or "\\?\" or "\\?\UNC\" or
	 * "\\?\Volume{GUID}\"
	 * (absolute path prefixes used by Windows API) */
	if (p[0] == L'\\' && p[1] == L'\\' &&
	    (p[2] == L'.' || p[2] == L'?') && p[3] ==  L'\\')
	{
		/* A path begin with "\\?\UNC\" */
		if (p[2] == L'?' &&
		    (p[4] == L'U' || p[4] == L'u') &&
		    (p[5] == L'N' || p[5] == L'n') &&
		    (p[6] == L'C' || p[6] == L'c') &&
		    p[7] == L'\\')
			p += 8;
		/* A path begin with "\\?\Volume{GUID}\" */
		else if (p[2] == L'?' &&
		    (p[4] == L'V' || p[4] == L'v') &&
		    (p[5] == L'O' || p[5] == L'o') &&
		    (p[6] == L'L' || p[6] == L'l') &&
		    (p[7] == L'U' || p[7] == L'u') &&
		    (p[8] == L'M' || p[8] == L'm') &&
		    (p[9] == L'E' || p[9] == L'e') &&
		    p[10] == L'{') {
			if (guidword(p+11, 8) == 0 && p[19] == L'-' &&
			    guidword(p+20, 4) == 0 && p[24] == L'-' &&
			    guidword(p+25, 4) == 0 && p[29] == L'-' &&
			    guidword(p+30, 4) == 0 && p[34] == L'-' &&
			    guidword(p+35, 12) == 0 && p[47] == L'}' &&
			    p[48] == L'\\')
				p += 49;
			else
				p += 4;
		/* A path begin with "\\.\PhysicalDriveX" */
		} else if (p[2] == L'.' &&
		    (p[4] == L'P' || p[4] == L'p') &&
		    (p[5] == L'H' || p[5] == L'h') &&
		    (p[6] == L'Y' || p[6] == L'y') &&
		    (p[7] == L'S' || p[7] == L's') &&
		    (p[8] == L'I' || p[8] == L'i') &&
		    (p[9] == L'C' || p[9] == L'c') &&
		    (p[9] == L'A' || p[9] == L'a') &&
		    (p[9] == L'L' || p[9] == L'l') &&
		    (p[9] == L'D' || p[9] == L'd') &&
		    (p[9] == L'R' || p[9] == L'r') &&
		    (p[9] == L'I' || p[9] == L'i') &&
		    (p[9] == L'V' || p[9] == L'v') &&
		    (p[9] == L'E' || p[9] == L'e') &&
		    (p[10] >= L'0' && p[10] <= L'9') &&
		    p[11] == L'\0') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Path is a physical drive name");
			return (ARCHIVE_FAILED);
		} else
			p += 4;
	}

	/* Skip leading drive letter from archives created
	 * on Windows. */
	if (((p[0] >= L'a' && p[0] <= L'z') ||
	     (p[0] >= L'A' && p[0] <= L'Z')) &&
		 p[1] == L':') {
		if (p[2] == L'\0') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Path is a drive name");
			return (ARCHIVE_FAILED);
		}
		if (p[2] == L'\\')
			p += 2;
	}

	top = dest = src = p;
	/* Rewrite the path name if its character is a unusable. */
	for (; *p != L'\0'; p++) {
		if (*p == L':' || *p == L'*' || *p == L'?' || *p == L'"' ||
		    *p == L'<' || *p == L'>' || *p == L'|')
			*p = L'_';
	}
	/* Skip leading '\'. */
	if (*src == L'\\')
		separator = *src++;

	/* Scan the pathname one element at a time. */
	for (;;) {
		/* src points to first char after '\' */
		if (src[0] == L'\0') {
			break;
		} else if (src[0] == L'\\') {
			/* Found '\\'('//'), ignore second one. */
			src++;
			continue;
		} else if (src[0] == L'.') {
			if (src[1] == L'\0') {
				/* Ignore trailing '.' */
				break;
			} else if (src[1] == L'\\') {
				/* Skip '.\'. */
				src += 2;
				continue;
			} else if (src[1] == L'.') {
				if (src[2] == L'\\' || src[2] == L'\0') {
					/* Conditionally warn about '..' */
					if (a->flags &
					    ARCHIVE_EXTRACT_SECURE_NODOTDOT) {
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_MISC,
						    "Path contains '..'");
						return (ARCHIVE_FAILED);
					}
				}
				/*
				 * Note: Under no circumstances do we
				 * remove '..' elements.  In
				 * particular, restoring
				 * '\foo\..\bar\' should create the
				 * 'foo' dir as a side-effect.
				 */
			}
		}

		/* Copy current element, including leading '\'. */
		if (separator)
			*dest++ = L'\\';
		while (*src != L'\0' && *src != L'\\') {
			*dest++ = *src++;
		}

		if (*src == L'\0')
			break;

		/* Skip '\' separator. */
		separator = *src++;
	}
	/*
	 * We've just copied zero or more path elements, not including the
	 * final '\'.
	 */
	if (dest == top) {
		/*
		 * Nothing got copied.  The path must have been something
		 * like '.' or '\' or './' or '/././././/./'.
		 */
		if (separator)
			*dest++ = L'\\';
		else
			*dest++ = L'.';
	}
	/* Terminate the result. */
	*dest = L'\0';
	return (ARCHIVE_OK);
}