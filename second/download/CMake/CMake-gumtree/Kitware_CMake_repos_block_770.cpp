{
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory "
					    " for Symlink");
					return (ARCHIVE_FATAL);
				}