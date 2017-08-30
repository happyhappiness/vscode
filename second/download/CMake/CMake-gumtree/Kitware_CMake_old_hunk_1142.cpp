		else {

			archive_set_error(&(a->archive),

			    ARCHIVE_ERRNO_MISC,

			    "Unkonwn checksum name: `%s'",

			    value);

			return (ARCHIVE_FAILED);

		}

