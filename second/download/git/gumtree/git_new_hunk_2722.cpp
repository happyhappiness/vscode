int cmd_mktag(int argc, const char **argv, const char *prefix)
{
	struct strbuf buf = STRBUF_INIT;
	unsigned char result_sha1[20];

	if (argc != 1)
		usage("git mktag");

	if (strbuf_read(&buf, 0, 4096) < 0) {
		die_errno("could not read from stdin");
	}

	/* Verify it for some basic sanity: it needs to start with
