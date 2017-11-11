static int verify_commit(const char *name, unsigned flags)
{
	enum object_type type;
	unsigned char sha1[20];
	char *buf;
	unsigned long size;
	int ret;

	if (get_sha1(name, sha1))
		return error("commit '%s' not found.", name);

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);
	if (type != OBJ_COMMIT)
		return error("%s: cannot verify a non-commit object of type %s.",
				name, typename(type));

	ret = run_gpg_verify(sha1, buf, size, flags);

	free(buf);
	return ret;
}