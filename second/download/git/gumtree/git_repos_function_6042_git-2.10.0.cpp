static int input_error(struct line_buffer *file)
{
	if (!buffer_ferror(file))
		return error("delta preimage ends early");
	return error_errno("cannot read delta preimage");
}