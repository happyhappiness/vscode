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
	   "object <sha1>\ntype\ntagger " */
	if (verify_tag(buf.buf, buf.len) < 0)
		die("invalid tag signature file");

	if (write_sha1_file(buf.buf, buf.len, tag_type, result_sha1) < 0)
		die("unable to write tag file");

	strbuf_release(&buf);
	printf("%s\n", sha1_to_hex(result_sha1));
	return 0;
}