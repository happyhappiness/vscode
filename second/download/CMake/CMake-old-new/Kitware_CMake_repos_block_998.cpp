{
				archive_string_free(&as);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}