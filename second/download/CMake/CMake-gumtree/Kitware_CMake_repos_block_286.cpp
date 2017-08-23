{
			archive_set_error(&a->archive, ENOMEM, "Out of memory");
			free(attr);
			free(name);
			free(value);
			return (ARCHIVE_FATAL);
		}