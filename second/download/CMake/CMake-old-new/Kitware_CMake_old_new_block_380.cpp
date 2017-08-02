{
			archive_set_error(f->archive, EIO,
			    "Can't write to filter");
			return (ARCHIVE_FATAL);
		}