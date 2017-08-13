{
			xar->opt_threads = 1;
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Illegal value `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}