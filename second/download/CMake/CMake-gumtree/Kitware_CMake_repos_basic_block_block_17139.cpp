{
		uuencode_line(a, shar, src, 45);
		src += 45;
		n -= 45;

		if (shar->work.length < 65536)
			continue;
		ret = __archive_write_output(a, shar->work.s,
		    shar->work.length);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		archive_string_empty(&shar->work);
	}