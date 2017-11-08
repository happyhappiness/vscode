static int mailinfo(FILE *in, FILE *out, const char *msg, const char *patch)
{
	int peek;
	fin = in;
	fout = out;

	cmitmsg = fopen(msg, "w");
	if (!cmitmsg) {
		perror(msg);
		return -1;
	}
	patchfile = fopen(patch, "w");
	if (!patchfile) {
		perror(patch);
		fclose(cmitmsg);
		return -1;
	}

	p_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*p_hdr_data));
	s_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*s_hdr_data));

	do {
		peek = fgetc(in);
	} while (isspace(peek));
	ungetc(peek, in);

	/* process the email header */
	while (read_one_header_line(&line, fin))
		check_header(&line, p_hdr_data, 1);

	handle_body();
	handle_info();

	return 0;
}