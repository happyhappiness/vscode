{
				archive_set_error(&a->archive, ERANGE,
				    "File name too long");
				return (ARCHIVE_WARN);
			}