{
				archive_string_free(&as);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				_isoent_free(isoent);
				*isoentpp = NULL;
				return (ARCHIVE_FATAL);
			}