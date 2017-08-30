

		if (!S_ISDIR(a->st.st_mode)) {

			/* A non-dir is in the way, unlink it. */

			if (a->flags & ARCHIVE_EXTRACT_CLEAR_NOCHANGE_FFLAGS)

				(void)clear_nochange_fflags(a);

			if (unlink(a->name) != 0) {

				archive_set_error(&a->archive, errno,

				    "Can't unlink already-existing object");

