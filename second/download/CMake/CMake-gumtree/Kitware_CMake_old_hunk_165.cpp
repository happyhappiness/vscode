				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Invalid Rockridge CL");

				return (NULL);

			}

			parent->subdirs++;

			/* Overwrite an offset and a number of this "CL" entry

