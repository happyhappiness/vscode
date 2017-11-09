static int show_text_ref(const char *name, const struct object_id *oid,
			 int flag, void *cb_data)
{
	const char *name_nons = strip_namespace(name);
	struct strbuf *buf = cb_data;
	struct object *o = parse_object(oid);
	if (!o)
		return 0;

	strbuf_addf(buf, "%s\t%s\n", oid_to_hex(oid), name_nons);
	if (o->type == OBJ_TAG) {
		o = deref_tag(o, name, 0);
		if (!o)
			return 0;
		strbuf_addf(buf, "%s\t%s^{}\n", oid_to_hex(&o->oid),
			    name_nons);
	}
	return 0;
}