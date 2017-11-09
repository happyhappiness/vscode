static int skip_or_whine(struct line_buffer *file, off_t gap)
{
	if (buffer_skip_bytes(file, gap) != gap)
		return input_error(file);
	return 0;
}