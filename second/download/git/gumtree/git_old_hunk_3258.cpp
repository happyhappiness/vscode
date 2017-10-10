
static int recvline_fh(FILE *helper, struct strbuf *buffer, const char *name)
{
	strbuf_reset(buffer);
	if (debug)
		fprintf(stderr, "Debug: Remote helper: Waiting...\n");
	if (strbuf_getline(buffer, helper, '\n') == EOF) {
		if (debug)
			fprintf(stderr, "Debug: Remote helper quit.\n");
		return 1;
	}

	if (debug)
