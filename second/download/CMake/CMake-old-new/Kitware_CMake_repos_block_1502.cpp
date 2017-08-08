{
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate filename buffer");
				return (ARCHIVE_FATAL);
			}