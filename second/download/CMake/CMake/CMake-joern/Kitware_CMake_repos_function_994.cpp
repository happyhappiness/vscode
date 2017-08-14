static int
file_gen_utility_names(struct archive_write *a, struct file *file)
{
	struct xar *xar;
	const char *pp;
	char *p, *dirname, *slash;
	size_t len;
	int r = ARCHIVE_OK;

	xar = (struct xar *)a->format_data;
	archive_string_empty(&(file->parentdir));
	archive_string_empty(&(file->basename));
	archive_string_empty(&(file->symlink));

	if (file->parent == file)/* virtual root */
		return (ARCHIVE_OK);

	if (archive_entry_pathname_l(file->entry, &pp, &len, xar->sconv)
	    != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to UTF-8",
		    archive_entry_pathname(file->entry));
		r = ARCHIVE_WARN;
	}
	archive_strncpy(&(file->parentdir), pp, len);
	len = file->parentdir.length;
	p = dirname = file->parentdir.s;
	/*
	 * Convert a path-separator from '\' to  '/'
	 */
	cleanup_backslash(p, len);

	/*
	 * Remove leading '/', '../' and './' elements
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
		} else if (p[1] == '/' || (p[1] == '.' && p[2] == '\0')) {
			p += 2;
			len -= 2;
		} else if (p[1] == '\0') {
			p++;
			len--;
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

	if (archive_entry_filetype(file->entry) == AE_IFLNK) {
		size_t len2;
		/* Convert symlink name too. */
		if (archive_entry_symlink_l(file->entry, &pp, &len2,
		    xar->sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate symlink '%s' to UTF-8",
			    archive_entry_symlink(file->entry));
			r = ARCHIVE_WARN;
		}
		archive_strncpy(&(file->symlink), pp, len2);
		cleanup_backslash(file->symlink.s, file->symlink.length);
	}
	/*
	 * - Count up directory elements.
	 * - Find out the position which points the last position of
	 *   path separator('/').
	 */
	slash = NULL;
	for (; *p != '\0'; p++)
		if (*p == '/')
			slash = p;
	if (slash == NULL) {
		/* The pathname doesn't have a parent directory. */
		file->parentdir.length = len;
		archive_string_copy(&(file->basename), &(file->parentdir));
		archive_string_empty(&(file->parentdir));
		*file->parentdir.s = '\0';
		return (r);
	}

	/* Make a basename from dirname and slash */
	*slash  = '\0';
	file->parentdir.length = slash - dirname;
	archive_strcpy(&(file->basename),  slash + 1);
	return (r);
}