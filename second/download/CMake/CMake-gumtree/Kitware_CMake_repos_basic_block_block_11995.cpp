{
		r = lzh_decode_init(&(lha->strm), lha->method);
		switch (r) {
		case ARCHIVE_OK:
			break;
		case ARCHIVE_FAILED:
        		/* Unsupported compression. */
			*buff = NULL;
			*size = 0;
			*offset = 0;
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unsupported lzh compression method -%c%c%c-",
			    lha->method[0], lha->method[1], lha->method[2]);
			/* We know compressed size; just skip it. */
			archive_read_format_lha_read_data_skip(a);
			return (ARCHIVE_WARN);
		default:
			archive_set_error(&a->archive, ENOMEM,
			    "Couldn't allocate memory "
			    "for lzh decompression");
			return (ARCHIVE_FATAL);
		}
		/* We've initialized decompression for this stream. */
		lha->decompress_init = 1;
		lha->strm.avail_out = 0;
		lha->strm.total_out = 0;
	}