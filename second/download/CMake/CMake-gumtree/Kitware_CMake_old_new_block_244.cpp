(pn[0] != '\0' && (pn[0] != '/' || pn[1] != '\0')) {
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