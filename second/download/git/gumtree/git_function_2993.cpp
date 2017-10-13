int gpg_verify_tag(const unsigned char *sha1, const char *name_to_report,
		unsigned flags)
{
	enum object_type type;
	char *buf;
	unsigned long size;
	int ret;

	type = sha1_object_info(sha1, NULL);
	if (type != OBJ_TAG)
		return error("%s: cannot verify a non-tag object of type %s.",
				name_to_report ?
				name_to_report :
				find_unique_abbrev(sha1, DEFAULT_ABBREV),
				typename(type));

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("%s: unable to read file.",
				name_to_report ?
				name_to_report :
				find_unique_abbrev(sha1, DEFAULT_ABBREV));

	ret = run_gpg_verify(buf, size, flags);

	free(buf);
	return ret;
}