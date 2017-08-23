static int
check_symlinks(struct archive_write_disk *a)
{
	wchar_t *pn, *p;
	wchar_t c;
	int r;
	BY_HANDLE_FILE_INFORMATION st;
	mode_t st_mode;

	/*
	 * Guard against symlink tricks.  Reject any archive entry whose
	 * destination would be altered by a symlink.
	 */
	/* Whatever we checked last time doesn't need to be re-checked. */
	pn = a->name;
	p = a->path_safe.s;
	while ((*pn != '\0') && (*p == *pn))
		++p, ++pn;
	c = pn[0];
	/* Keep going until we've checked the entire name. */
	while (pn[0] != '\0' && (pn[0] != '\\' || pn[1] != '\0')) {
		/* Skip the next path element. */
		while (*pn != '\0' && *pn != '\\')
			++pn;
		c = pn[0];
		pn[0] = '\0';
		/* Check that we haven't hit a symlink. */
		r = file_information(a, a->name, &st, &st_mode, 1);
		if (r != 0) {
			/* We've hit a dir that doesn't exist; stop now. */
			if (errno == ENOENT)
				break;
		} else if (S_ISLNK(st_mode)) {
			if (c == '\0') {
				/*
				 * Last element is symlink; remove it
				 * so we can overwrite it with the
				 * item being extracted.
				 */
				if (disk_unlink(a->name)) {
					archive_set_error(&a->archive, errno,
					    "Could not remove symlink %ls",
					    a->name);
					pn[0] = c;
					return (ARCHIVE_FAILED);
				}
				a->pst = NULL;
				/*
				 * Even if we did remove it, a warning
				 * is in order.  The warning is silly,
				 * though, if we're just replacing one
				 * symlink with another symlink.
				 */
				if (!S_ISLNK(a->mode)) {
					archive_set_error(&a->archive, 0,
					    "Removing symlink %ls",
					    a->name);
				}
				/* Symlink gone.  No more problem! */
				pn[0] = c;
				return (0);
			} else if (a->flags & ARCHIVE_EXTRACT_UNLINK) {
				/* User asked us to remove problems. */
				if (disk_unlink(a->name) != 0) {
					archive_set_error(&a->archive, 0,
					    "Cannot remove intervening "
					    "symlink %ls", a->name);
					pn[0] = c;
					return (ARCHIVE_FAILED);
				}
				a->pst = NULL;
			} else {
				archive_set_error(&a->archive, 0,
				    "Cannot extract through symlink %ls",
				    a->name);
				pn[0] = c;
				return (ARCHIVE_FAILED);
			}
		}
	}
	pn[0] = c;
	/* We've checked and/or cleaned the whole path, so remember it. */
	archive_wstrcpy(&a->path_safe, a->name);
	return (ARCHIVE_OK);
}