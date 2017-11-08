static int verify_object(const unsigned char *sha1, const char *expected_type)
{
	int ret = -1;
	enum object_type type;
	unsigned long size;
	void *buffer = read_sha1_file(sha1, &type, &size);
	const unsigned char *repl = lookup_replace_object(sha1);

	if (buffer) {
		if (type == type_from_string(expected_type))
			ret = check_sha1_signature(repl, buffer, size, expected_type);
		free(buffer);
	}
	return ret;
}