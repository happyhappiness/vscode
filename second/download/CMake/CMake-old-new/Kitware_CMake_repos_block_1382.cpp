{
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}