void fast_export_data(uint32_t mode, off_t len, struct line_buffer *input)
{
	assert(len >= 0);
	if (mode == REPO_MODE_LNK) {
		/* svn symlink blobs start with "link " */
		if (len < 5)
			die("invalid dump: symlink too short for \"link\" prefix");
		len -= 5;
		if (buffer_skip_bytes(input, 5) != 5)
			die_short_read(input);
	}
	printf("data %"PRIuMAX"\n", (uintmax_t) len);
	if (buffer_copy_bytes(input, len) != len)
		die_short_read(input);
	fputc('\n', stdout);
}