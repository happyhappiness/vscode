{
				archive_set_error(&(a->archive), errno,
				    "lseek failed");
				return (ARCHIVE_FATAL);
			}