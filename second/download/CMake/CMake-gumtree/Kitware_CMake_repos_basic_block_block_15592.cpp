{
		ret = __archive_write_output(a, filename, strlen(filename));
		if (ret != ARCHIVE_OK)
			return (ret);
		ar->entry_bytes_remaining -= strlen(filename);
	}