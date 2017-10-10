
static const char * const verify_tag_usage[] = {
		N_("git verify-tag [-v | --verbose] <tag>..."),
		NULL
};

static int run_gpg_verify(const char *buf, unsigned long size, unsigned flags)
{
	struct signature_check sigc;
	int len;
	int ret;

	memset(&sigc, 0, sizeof(sigc));

	len = parse_signature(buf, size);

	if (size == len) {
		if (flags & GPG_VERIFY_VERBOSE)
			write_in_full(1, buf, len);
		return error("no signature found");
	}

	ret = check_signature(buf, len, buf + len, size - len, &sigc);
	print_signature_buffer(&sigc, flags);

	signature_check_clear(&sigc);
	return ret;
}

static int verify_tag(const char *name, unsigned flags)
{
	enum object_type type;
	unsigned char sha1[20];
	char *buf;
	unsigned long size;
	int ret;
