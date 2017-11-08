static void convert_date(void *buffer, unsigned long size, unsigned char *result_sha1)
{
	char *new = xmalloc(size + 100);
	unsigned long newlen = 0;

	/* "tree <sha1>\n" */
	memcpy(new + newlen, buffer, 46);
	newlen += 46;
	buffer = (char *) buffer + 46;
	size -= 46;

	/* "parent <sha1>\n" */
	while (!memcmp(buffer, "parent ", 7)) {
		memcpy(new + newlen, buffer, 48);
		newlen += 48;
		buffer = (char *) buffer + 48;
		size -= 48;
	}

	/* "author xyz <xyz> date" */
	newlen += convert_date_line(new + newlen, &buffer, &size);
	/* "committer xyz <xyz> date" */
	newlen += convert_date_line(new + newlen, &buffer, &size);

	/* Rest */
	memcpy(new + newlen, buffer, size);
	newlen += size;

	write_sha1_file(new, newlen, commit_type, result_sha1);
	free(new);
}