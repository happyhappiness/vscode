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

