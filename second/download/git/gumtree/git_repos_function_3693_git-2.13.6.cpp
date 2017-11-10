static int read_oid_strbuf(struct merge_options *o,
	const struct object_id *oid, struct strbuf *dst)
{
	void *buf;
	enum object_type type;
	unsigned long size;
	buf = read_sha1_file(oid->hash, &type, &size);
	if (!buf)
		return err(o, _("cannot read object %s"), oid_to_hex(oid));
	if (type != OBJ_BLOB) {
		free(buf);
		return err(o, _("object %s is not a blob"), oid_to_hex(oid));
	}
	strbuf_attach(dst, buf, size, size + 1);
	return 0;
}