static int verify_commit(const char *name, unsigned flags)
{
	enum object_type type;
	struct object_id oid;
	char *buf;
	unsigned long size;
	int ret;

	if (get_oid(name, &oid))
		return error("commit '%s' not found.", name);

	buf = read_sha1_file(oid.hash, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);
	if (type != OBJ_COMMIT)
		return error("%s: cannot verify a non-commit object of type %s.",
				name, typename(type));

	ret = run_gpg_verify(&oid, buf, size, flags);

	free(buf);
	return ret;
}