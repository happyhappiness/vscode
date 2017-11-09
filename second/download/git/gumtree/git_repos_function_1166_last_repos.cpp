int mbs_chrlen(const char **text, size_t *remainder_p, const char *encoding)
{
	int chrlen;
	const char *p = *text;
	size_t r = (remainder_p ? *remainder_p : SIZE_MAX);

	if (r < 1)
		return 0;

	if (is_encoding_utf8(encoding)) {
		pick_one_utf8_char(&p, &r);

		chrlen = p ? (p - *text)
			   : 1 /* not valid UTF-8 -> raw byte sequence */;
	}
	else {
		/*
		 * TODO use iconv to decode one char and obtain its chrlen
		 * for now, let's treat encodings != UTF-8 as one-byte
		 */
		chrlen = 1;
	}

	*text += chrlen;
	if (remainder_p)
		*remainder_p -= chrlen;

	return chrlen;
}