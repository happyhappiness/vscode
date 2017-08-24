{
		ret = __archive_write_output(archive, "/", 1);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		written_bytes += 1;
	}