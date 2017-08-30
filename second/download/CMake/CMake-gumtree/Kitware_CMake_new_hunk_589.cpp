			en = create_filesystem_object(a);

		} else if (!S_ISDIR(a->mode)) {

			/* A dir is in the way of a non-dir, rmdir it. */

			if (a->flags & ARCHIVE_EXTRACT_CLEAR_NOCHANGE_FFLAGS)

				(void)clear_nochange_fflags(a);

			if (rmdir(a->name) != 0) {

				archive_set_error(&a->archive, errno,

				    "Can't replace existing directory with non-directory");

