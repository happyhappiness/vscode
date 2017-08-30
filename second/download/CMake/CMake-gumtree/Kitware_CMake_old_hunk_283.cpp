	return (a->current_fixup);
}

/* TODO: Make this work. */
/*
 * TODO: The deep-directory support bypasses this; disable deep directory
 * support if we're doing symlink checks.
 */
/*
 * TODO: Someday, integrate this with the deep dir support; they both
 * scan the path and both can be optimized by comparing against other
 * recent paths.
 */
/* TODO: Extend this to support symlinks on Windows Vista and later. */
static int
check_symlinks(struct archive_write_disk *a)
{
#if !defined(HAVE_LSTAT)
	/* Platform doesn't have lstat, so we can't look for symlinks. */
	(void)a; /* UNUSED */
	return (ARCHIVE_OK);
#else
	char *pn;
	char c;
	int r;
	struct stat st;

	/*
	 * Guard against symlink tricks.  Reject any archive entry whose
	 * destination would be altered by a symlink.
	 */
	/* Whatever we checked last time doesn't need to be re-checked. */
	pn = a->name;
	if (archive_strlen(&(a->path_safe)) > 0) {
		char *p = a->path_safe.s;
		while ((*pn != '\0') && (*p == *pn))
			++p, ++pn;
	}
	/* Skip the root directory if the path is absolute. */
	if(pn == a->name && pn[0] == '/')
		++pn;
	c = pn[0];
	/* Keep going until we've checked the entire name. */
	while (pn[0] != '\0' && (pn[0] != '/' || pn[1] != '\0')) {
		/* Skip the next path element. */
		while (*pn != '\0' && *pn != '/')
			++pn;
		c = pn[0];
		pn[0] = '\0';
		/* Check that we haven't hit a symlink. */
		r = lstat(a->name, &st);
		if (r != 0) {
			/* We've hit a dir that doesn't exist; stop now. */
			if (errno == ENOENT)
				break;
		} else if (S_ISLNK(st.st_mode)) {
			if (c == '\0') {
				/*
				 * Last element is symlink; remove it
				 * so we can overwrite it with the
				 * item being extracted.
				 */
				if (unlink(a->name)) {
					archive_set_error(&a->archive, errno,
					    "Could not remove symlink %s",
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
					    "Removing symlink %s",
					    a->name);
				}
				/* Symlink gone.  No more problem! */
				pn[0] = c;
				return (0);
			} else if (a->flags & ARCHIVE_EXTRACT_UNLINK) {
				/* User asked us to remove problems. */
				if (unlink(a->name) != 0) {
					archive_set_error(&a->archive, 0,
					    "Cannot remove intervening symlink %s",
					    a->name);
					pn[0] = c;
					return (ARCHIVE_FAILED);
				}
				a->pst = NULL;
			} else {
				archive_set_error(&a->archive, 0,
				    "Cannot extract through symlink %s",
				    a->name);
				pn[0] = c;
				return (ARCHIVE_FAILED);
			}
		}
		pn[0] = c;
		if (pn[0] != '\0')
			pn++; /* Advance to the next segment. */
	}
	pn[0] = c;
	/* We've checked and/or cleaned the whole path, so remember it. */
	archive_strcpy(&a->path_safe, a->name);
	return (ARCHIVE_OK);
#endif
}

#if defined(__CYGWIN__)
/*
 * 1. Convert a path separator from '\' to '/' .
