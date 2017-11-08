static int read_blob_object(struct strbuf *buf, const unsigned char *sha1, unsigned mode)
{
	if (S_ISGITLINK(mode)) {
		strbuf_grow(buf, 100);
		strbuf_addf(buf, "Subproject commit %s\n", sha1_to_hex(sha1));
	} else {
		enum object_type type;
		unsigned long sz;
		char *result;

		result = read_sha1_file(sha1, &type, &sz);
		if (!result)
			return -1;
		/* XXX read_sha1_file NUL-terminates */
		strbuf_attach(buf, result, sz, sz + 1);
	}
	return 0;
}