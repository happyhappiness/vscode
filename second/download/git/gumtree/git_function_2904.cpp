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