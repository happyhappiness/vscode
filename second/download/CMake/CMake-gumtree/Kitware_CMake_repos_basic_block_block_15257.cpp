{
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
			}