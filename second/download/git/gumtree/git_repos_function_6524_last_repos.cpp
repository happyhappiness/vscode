static int read_offset(struct line_buffer *in, off_t *result, off_t *len)
{
	uintmax_t val;
	if (read_int(in, &val, len))
		return -1;
	if (val > maximum_signed_value_of_type(off_t))
		return error("unrepresentable offset in delta: %"PRIuMAX"", val);
	*result = val;
	return 0;
}