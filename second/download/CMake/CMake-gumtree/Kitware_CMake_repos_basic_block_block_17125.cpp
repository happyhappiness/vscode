{
	static const size_t ensured = 65533;
	struct shar *shar;
	const char *src;
	char *buf, *buf_end;
	int ret;
	size_t written = n;

	shar = (struct shar *)a->format_data;
	if (!shar->has_data || n == 0)
		return (0);

	src = (const char *)buff;

	/*
	 * ensure is the number of bytes in buffer before expanding the
	 * current character.  Each operation writes the current character
	 * and optionally the start-of-new-line marker.  This can happen
	 * twice before entering the loop, so make sure three additional
	 * bytes can be written.
	 */
	if (archive_string_ensure(&shar->work, ensured + 3) == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}

	if (shar->work.length > ensured) {
		ret = __archive_write_output(a, shar->work.s,
		    shar->work.length);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		archive_string_empty(&shar->work);
	}
	buf = shar->work.s + shar->work.length;
	buf_end = shar->work.s + ensured;

	if (shar->end_of_line) {
		*buf++ = 'X';
		shar->end_of_line = 0;
	}

	while (n-- != 0) {
		if ((*buf++ = *src++) == '\n') {
			if (n == 0)
				shar->end_of_line = 1;
			else
				*buf++ = 'X';
		}

		if (buf >= buf_end) {
			shar->work.length = buf - shar->work.s;
			ret = __archive_write_output(a, shar->work.s,
			    shar->work.length);
			if (ret != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			archive_string_empty(&shar->work);
			buf = shar->work.s;
		}
	}

	shar->work.length = buf - shar->work.s;

	return (written);
}