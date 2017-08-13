{
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate ustar data");
				archive_wstring_free(&ws);
				return(ARCHIVE_FATAL);
			}