{
				archive_set_error(&a->archive, errno,
				    "No memory");
				return (ARCHIVE_FATAL);
			}