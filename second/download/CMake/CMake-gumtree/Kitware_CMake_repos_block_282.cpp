{
			free(attr->name);
			free(attr);
			archive_set_error(&a->archive, ENOMEM, "Out of memory");
			return (ARCHIVE_FATAL);
		}