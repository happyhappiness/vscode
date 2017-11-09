static int read_length(struct line_buffer *in, size_t *result, off_t *len)
{
	uintmax_t val;
	if (read_int(in, &val, len))
		return -1;
	if (val > SIZE_MAX)
		return error("unrepresentable length in delta: %"PRIuMAX"", val);
	*result = val;
	return 0;
}