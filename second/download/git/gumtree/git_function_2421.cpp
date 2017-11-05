static void feed_object(const unsigned char *sha1, FILE *fh, int negative)
{
	if (negative && !has_sha1_file(sha1))
		return;

	if (negative)
		putc('^', fh);
	fputs(sha1_to_hex(sha1), fh);
	putc('\n', fh);
}