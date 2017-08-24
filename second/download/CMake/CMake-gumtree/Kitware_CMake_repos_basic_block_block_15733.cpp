{
		size_t length = gnutar->linkname_length + 1;
		struct archive_entry *temp = archive_entry_new2(&a->archive);

		/* Uname/gname here don't really matter since no one reads them;
		 * these are the values that GNU tar happens to use on FreeBSD. */
		archive_entry_set_uname(temp, "root");
		archive_entry_set_gname(temp, "wheel");

		archive_entry_set_pathname(temp, "././@LongLink");
		archive_entry_set_size(temp, length);
		ret = archive_format_gnutar_header(a, buff, temp, 'K');
		archive_entry_free(temp);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		ret = __archive_write_output(a, buff, 512);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Write name and trailing null byte. */
		ret = __archive_write_output(a, gnutar->linkname, length);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Pad to 512 bytes */
		ret = __archive_write_nulls(a, 0x1ff & (-(ssize_t)length));
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
	}