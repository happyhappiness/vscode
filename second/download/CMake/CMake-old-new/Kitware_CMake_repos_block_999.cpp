{
				archive_string_free(&as);
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "A name buffer is too small");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}