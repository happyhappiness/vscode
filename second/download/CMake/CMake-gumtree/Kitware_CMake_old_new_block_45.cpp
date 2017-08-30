{
				/* Warn about other extended attributes. */
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Can't restore extended attribute ``%s''",
				    name);
				ret = ARCHIVE_WARN;
				continue;
			}