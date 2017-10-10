
static const char * const verify_tag_usage[] = {
		N_("git verify-tag [-v | --verbose] <tag>..."),
		NULL
};

static int run_gpg_verify(const char *buf, unsigned long size, int verbose)
{
	int len;

	len = parse_signature(buf, size);
	if (verbose)
		write_in_full(1, buf, len);

	if (size == len)
		return error("no signature found");

	return verify_signed_buffer(buf, len, buf + len, size - len, NULL, NULL);
}

static int verify_tag(const char *name, int verbose)
{
	enum object_type type;
	unsigned char sha1[20];
	char *buf;
	unsigned long size;
	int ret;
