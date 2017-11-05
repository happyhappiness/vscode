static int parse_reuse_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;
	char *buf;
	unsigned char object[20];
	enum object_type type;
	unsigned long len;

	if (d->buf.len)
		strbuf_addch(&d->buf, '\n');

	if (get_sha1(arg, object))
		die(_("Failed to resolve '%s' as a valid ref."), arg);
	if (!(buf = read_sha1_file(object, &type, &len))) {
		free(buf);
		die(_("Failed to read object '%s'."), arg);
	}
	if (type != OBJ_BLOB) {
		free(buf);
		die(_("Cannot read note data from non-blob object '%s'."), arg);
	}
	strbuf_add(&d->buf, buf, len);
	free(buf);

	d->given = 1;
	return 0;
}