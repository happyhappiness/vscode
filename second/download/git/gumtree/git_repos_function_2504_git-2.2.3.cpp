static int show_text_ref(const char *name, const unsigned char *sha1,
	int flag, void *cb_data)
{
	const char *name_nons = strip_namespace(name);
	struct strbuf *buf = cb_data;
	struct object *o = parse_object(sha1);
	if (!o)
		return 0;

	strbuf_addf(buf, "%s\t%s\n", sha1_to_hex(sha1), name_nons);
	if (o->type == OBJ_TAG) {
		o = deref_tag(o, name, 0);
		if (!o)
			return 0;
		strbuf_addf(buf, "%s\t%s^{}\n", sha1_to_hex(o->sha1),
			    name_nons);
	}
	return 0;
}