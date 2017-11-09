static int read_blob_object(struct strbuf *buf, const struct object_id *oid, unsigned mode)
{
	if (S_ISGITLINK(mode)) {
		strbuf_grow(buf, 100);
		strbuf_addf(buf, "Subproject commit %s\n", oid_to_hex(oid));
	} else {
		enum object_type type;
		unsigned long sz;
		char *result;

		result = read_sha1_file(oid->hash, &type, &sz);
		if (!result)
			return -1;
		/* XXX read_sha1_file NUL-terminates */
		strbuf_attach(buf, result, sz, sz + 1);
	}
	return 0;
}