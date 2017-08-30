			return ARCHIVE_FATAL;

		}



		if (archive_entry_copy_symlink_l(entry, p, linkname_length,

		    NULL) != 0) {

			/* NOTE: If the last argument is NULL, this will

			 * fail only by memeory allocation failure. */

			archive_set_error(&a->archive, ENOMEM,

			    "Can't allocate memory for Symlink");

			return (ARCHIVE_FATAL);

		}

		/* TODO: handle character-set issues? */

	}

	return ARCHIVE_OK;

}



static int

