{
	struct shar *shar;
	const char *src;
	size_t n;
	int ret;

	shar = (struct shar *)a->format_data;
	if (!shar->has_data)
		return (ARCHIVE_OK);
	src = (const char *)buff;

	if (shar->outpos != 0) {
		n = 45 - shar->outpos;
		if (n > length)
			n = length;
		memcpy(shar->outbuff + shar->outpos, src, n);
		if (shar->outpos + n < 45) {
			shar->outpos += n;
			return length;
		}
		uuencode_line(a, shar, shar->outbuff, 45);
		src += n;
		n = length - n;
	} else {
		n = length;
	}

	while (n >= 45) {
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
	if (n != 0) {
		memcpy(shar->outbuff, src, n);
		shar->outpos = n;
	}
	return (length);
}