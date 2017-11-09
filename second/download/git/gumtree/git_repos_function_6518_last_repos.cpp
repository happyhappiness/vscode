static int write_strbuf(struct strbuf *sb, FILE *out)
{
	if (fwrite(sb->buf, 1, sb->len, out) == sb->len)	/* Success. */
		return 0;
	return error_errno("cannot write delta postimage");
}