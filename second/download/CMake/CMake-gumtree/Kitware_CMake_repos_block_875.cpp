{
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			ret_final = ARCHIVE_FATAL;
			goto exit_write_header;
		}