
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

	if (get_sha1(name, sha1))
		return error("tag '%s' not found.", name);

	type = sha1_object_info(sha1, NULL);
	if (type != OBJ_TAG)
		return error("%s: cannot verify a non-tag object of type %s.",
				name, typename(type));

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);

	ret = run_gpg_verify(buf, size, flags);

	free(buf);
	return ret;
}

static int git_verify_tag_config(const char *var, const char *value, void *cb)
{
	int status = git_gpg_config(var, value, cb);
	if (status)
		return status;
	return git_default_config(var, value, cb);
