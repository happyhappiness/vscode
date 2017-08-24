{
	int bits_checked;

	(void)self; /* UNUSED */

	if (peek_at_header(filter, &bits_checked))
		return (bits_checked);
	return (0);
}