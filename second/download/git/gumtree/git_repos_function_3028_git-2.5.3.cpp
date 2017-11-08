static int read_sha1_strbuf(const unsigned char *sha1, struct strbuf *dst)
{
	void *buf;
	enum object_type type;
	unsigned long size;
	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error(_("cannot read object %s"), sha1_to_hex(sha1));
	if (type != OBJ_BLOB) {
		free(buf);
		return error(_("object %s is not a blob"), sha1_to_hex(sha1));
	}
	strbuf_attach(dst, buf, size, size + 1);
	return 0;
}