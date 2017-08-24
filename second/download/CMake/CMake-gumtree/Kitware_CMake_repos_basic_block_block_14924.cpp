{
#if !HAVE_LINK
		return (EPERM);
#else
		archive_string_init(&error_string);
		linkname_copy = strdup(linkname);
		if (linkname_copy == NULL) {
		    return (EPERM);
		}
		/*
		 * TODO: consider using the cleaned-up path as the link
		 * target?
		 */
		r = cleanup_pathname_fsobj(linkname_copy, &error_number,
		    &error_string, a->flags);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, error_number, "%s",
			    error_string.s);
			free(linkname_copy);
			archive_string_free(&error_string);
			/*
			 * EPERM is more appropriate than error_number for our
			 * callers
			 */
			return (EPERM);
		}
		r = check_symlinks_fsobj(linkname_copy, &error_number,
		    &error_string, a->flags);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, error_number, "%s",
			    error_string.s);
			free(linkname_copy);
			archive_string_free(&error_string);
			/*
			 * EPERM is more appropriate than error_number for our
			 * callers
			 */
			return (EPERM);
		}
		free(linkname_copy);
		archive_string_free(&error_string);
		r = link(linkname, a->name) ? errno : 0;
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
#ifdef HAVE_LSTAT
			r = lstat(a->name, &st);
#else
			r = stat(a->name, &st);
#endif
			if (r != 0)
				r = errno;
			else if ((st.st_mode & AE_IFMT) == AE_IFREG) {
				a->fd = open(a->name, O_WRONLY | O_TRUNC |
				    O_BINARY | O_CLOEXEC | O_NOFOLLOW);
				__archive_ensure_cloexec_flag(a->fd);
				if (a->fd < 0)
					r = errno;
			}
		}
		return (r);
#endif
	}