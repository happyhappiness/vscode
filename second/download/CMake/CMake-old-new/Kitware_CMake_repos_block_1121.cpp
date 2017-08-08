{
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate ustar data");
				archive_string_free(&as);
				return(ARCHIVE_FATAL);
			}