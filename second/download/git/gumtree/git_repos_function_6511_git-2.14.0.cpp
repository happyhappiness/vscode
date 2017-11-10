static int parse_first_operand(const char **buf, size_t *out, const char *end)
{
	size_t result = (unsigned char) *(*buf)++ & OPERAND_MASK;
	if (result) {	/* immediate operand */
		*out = result;
		return 0;
	}
	return parse_int(buf, out, end);
}