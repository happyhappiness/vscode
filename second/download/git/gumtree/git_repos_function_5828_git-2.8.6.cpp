static int read_int(struct line_buffer *in, uintmax_t *result, off_t *len)
{
	uintmax_t rv = 0;
	off_t sz;
	for (sz = *len; sz; sz--) {
		const int ch = buffer_read_char(in);
		if (ch == EOF)
			break;

		rv <<= VLI_BITS_PER_DIGIT;
		rv += (ch & VLI_DIGIT_MASK);
		if (ch & VLI_CONTINUE)
			continue;

		*result = rv;
		*len = sz - 1;
		return 0;
	}
	return error_short_read(in);
}