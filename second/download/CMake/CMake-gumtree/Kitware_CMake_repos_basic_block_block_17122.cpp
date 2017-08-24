(n-- != 0) {
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