{
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate strtab buffer");
			return (ARCHIVE_FATAL);
		}