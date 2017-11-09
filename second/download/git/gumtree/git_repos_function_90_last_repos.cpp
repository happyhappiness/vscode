static int last_line_length(struct strbuf *sb)
{
	int i;

	/* How many bytes are already used on the last line? */
	for (i = sb->len - 1; i >= 0; i--)
		if (sb->buf[i] == '\n')
			break;
	return sb->len - (i + 1);
}