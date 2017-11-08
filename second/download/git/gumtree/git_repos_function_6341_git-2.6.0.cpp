static void convert_commit(void *buffer, unsigned long size, unsigned char *result_sha1)
{
	void *orig_buffer = buffer;
	unsigned long orig_size = size;

	if (memcmp(buffer, "tree ", 5))
		die("Bad commit '%s'", (char *) buffer);
	convert_ascii_sha1((char *) buffer + 5);
	buffer = (char *) buffer + 46;    /* "tree " + "hex sha1" + "\n" */
	while (!memcmp(buffer, "parent ", 7)) {
		convert_ascii_sha1((char *) buffer + 7);
		buffer = (char *) buffer + 48;
	}
	convert_date(orig_buffer, orig_size, result_sha1);
}