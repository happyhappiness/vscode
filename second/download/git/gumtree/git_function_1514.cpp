static int split_one(FILE *mbox, const char *name, int allow_bare)
{
	FILE *output;
	int fd;
	int status = 0;
	int is_bare = !is_from_line(buf.buf, buf.len);

	if (is_bare && !allow_bare) {
		fprintf(stderr, "corrupt mailbox\n");
		exit(1);
	}
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd < 0)
		die_errno("cannot open output file '%s'", name);
	output = xfdopen(fd, "w");

	/* Copy it out, while searching for a line that begins with
	 * "From " and having something that looks like a date format.
	 */
	for (;;) {
		if (!keep_cr && buf.len > 1 && buf.buf[buf.len-1] == '\n' &&
			buf.buf[buf.len-2] == '\r') {
			strbuf_setlen(&buf, buf.len-2);
			strbuf_addch(&buf, '\n');
		}

		if (fwrite(buf.buf, 1, buf.len, output) != buf.len)
			die_errno("cannot write output");

		if (strbuf_getwholeline(&buf, mbox, '\n')) {
			if (feof(mbox)) {
				status = 1;
				break;
			}
			die_errno("cannot read mbox");
		}
		if (!is_bare && is_from_line(buf.buf, buf.len))
			break; /* done with one message */
	}
	fclose(output);
	return status;
}