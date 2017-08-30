				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Invalid Rockridge CL");

				goto fail;

			}

			parent->subdirs++;

			/* Overwrite an offset and a number of this "CL" entry

