void write_char_bufs(char *buf)
{
	/* Write the size of the string which will follow  */

	char b[4];

	SIVAL(b, 0, buf != NULL ? strlen(buf) : 0);

	write_batch_flist_file(b, sizeof(int));

	/*  Write the string if there is one */

	if (buf != NULL) {
		write_batch_flist_file(buf, strlen(buf));
	}
}