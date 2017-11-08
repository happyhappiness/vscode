static void lf_to_crlf(struct strbuf *msg)
{
	char *new;
	size_t i, j;
	char lastc;

	/* First pass: tally, in j, the size of the new string: */
	for (i = j = 0, lastc = '\0'; i < msg->len; i++) {
		if (msg->buf[i] == '\n' && lastc != '\r')
			j++; /* a CR will need to be added here */
		lastc = msg->buf[i];
		j++;
	}

	new = xmallocz(j);

	/*
	 * Second pass: write the new string.  Note that this loop is
	 * otherwise identical to the first pass.
	 */
	for (i = j = 0, lastc = '\0'; i < msg->len; i++) {
		if (msg->buf[i] == '\n' && lastc != '\r')
			new[j++] = '\r';
		lastc = new[j++] = msg->buf[i];
	}
	strbuf_attach(msg, new, j, j + 1);
}