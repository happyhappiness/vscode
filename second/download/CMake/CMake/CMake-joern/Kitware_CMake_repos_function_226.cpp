static int
mtree_entry_setup_filenames(struct archive_write *a, struct mtree_entry *file,
    struct archive_entry *entry)
{
	const char *pathname;
	char *p, *dirname, *slash;
	size_t len;
	int ret = ARCHIVE_OK;

	archive_strcpy(&file->pathname, archive_entry_pathname(entry));
#if defined(_WIN32) || defined(__CYGWIN__)
	/*
	 * Convert a path-separator from '\' to  '/'
	 */
	if (cleanup_backslash_1(file->pathname.s) != 0) {
		const wchar_t *wp = archive_entry_pathname_w(entry);
		struct archive_wstring ws;

		if (wp != NULL) {
			int r;
			archive_string_init(&ws);
			archive_wstrcpy(&ws, wp);
			cleanup_backslash_2(ws.s);
			archive_string_empty(&(file->pathname));
			r = archive_string_append_from_wcs(&(file->pathname),
			    ws.s, ws.length);
			archive_wstring_free(&ws);
			if (r < 0 && errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				return (ARCHIVE_FATAL);
			}
		}
	}
#else
	(void)a; /* UNUSED */
#endif
	pathname =  file->pathname.s;
	if (strcmp(pathname, ".") == 0) {
		archive_strcpy(&file->basename, ".");
		return (ARCHIVE_OK);
	}

	archive_strcpy(&(file->parentdir), pathname);

	len = file->parentdir.length;
	p = dirname = file->parentdir.s;

	/*
	 * Remove leading '/' and '../' elements
	 */
	while (*p) {
		if (p[0] == '/') {
			p++;
			len--;
		} else if (p[0] != '.')
			break;
		else if (p[1] == '.' && p[2] == '/') {
			p += 3;
			len -= 3;
		} else
			break;
	}
	if (p != dirname) {
		memmove(dirname, p, len+1);
		p = dirname;
	}
	/*
	 * Remove "/","/." and "/.." elements from tail.
	 */
	while (len > 0) {
		size_t ll = len;

		if (len > 0 && p[len-1] == '/') {
			p[len-1] = '\0';
			len--;
		}
		if (len > 1 && p[len-2] == '/' && p[len-1] == '.') {
			p[len-2] = '\0';
			len -= 2;
		}
		if (len > 2 && p[len-3] == '/' && p[len-2] == '.' &&
		    p[len-1] == '.') {
			p[len-3] = '\0';
			len -= 3;
		}
		if (ll == len)
			break;
	}
	while (*p) {
		if (p[0] == '/') {
			if (p[1] == '/')
				/* Convert '//' --> '/' */
				strcpy(p, p+1);
			else if (p[1] == '.' && p[2] == '/')
				/* Convert '/./' --> '/' */
				strcpy(p, p+2);
			else if (p[1] == '.' && p[2] == '.' && p[3] == '/') {
				/* Convert 'dir/dir1/../dir2/'
				 *     --> 'dir/dir2/'
				 */
				char *rp = p -1;
				while (rp >= dirname) {
					if (*rp == '/')
						break;
					--rp;
				}
				if (rp > dirname) {
					strcpy(rp, p+3);
					p = rp;
				} else {
					strcpy(dirname, p+4);
					p = dirname;
				}
			} else
				p++;
		} else
			p++;
	}
	p = dirname;
	len = strlen(p);

	/*
	 * Add "./" prefix.
	 * NOTE: If the pathname does not have a path separator, we have
	 * to add "./" to the head of the pathname because mtree reader
	 * will suppose that it is v1(a.k.a classic) mtree format and
	 * change the directory unexpectedly and so it will make a wrong
	 * path.
	 */
	if (strcmp(p, ".") != 0 && strncmp(p, "./", 2) != 0) {
		struct archive_string as;
		archive_string_init(&as);
		archive_strcpy(&as, "./");
		archive_strncat(&as, p, len);
		archive_string_empty(&file->parentdir);
		archive_string_concat(&file->parentdir, &as);
		archive_string_free(&as);
		p = file->parentdir.s;
		len = archive_strlen(&file->parentdir);
	}

	/*
	 * Find out the position which points the last position of
	 * path separator('/').
	 */
	slash = NULL;
	for (; *p != '\0'; p++) {
		if (*p == '/')
			slash = p;
	}
	if (slash == NULL) {
		/* The pathname doesn't have a parent directory. */
		file->parentdir.length = len;
		archive_string_copy(&(file->basename), &(file->parentdir));
		archive_string_empty(&(file->parentdir));
		*file->parentdir.s = '\0';
		return (ret);
	}

	/* Make a basename from file->parentdir.s and slash */
	*slash  = '\0';
	file->parentdir.length = slash - file->parentdir.s;
	archive_strcpy(&(file->basename),  slash + 1);
	return (ret);
}