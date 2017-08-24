{
		ret = __archive_write_output(a, shar->work.s,
		    shar->work.length);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		archive_string_empty(&shar->work);
	}