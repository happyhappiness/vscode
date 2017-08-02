{
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for Pathname");
				return (ARCHIVE_FATAL);
			}