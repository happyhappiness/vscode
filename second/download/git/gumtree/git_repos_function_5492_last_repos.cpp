static const char *describe_object(struct object *obj)
{
	static struct strbuf buf = STRBUF_INIT;
	char *name = name_objects ?
		lookup_decoration(fsck_walk_options.object_names, obj) : NULL;

	strbuf_reset(&buf);
	strbuf_addstr(&buf, oid_to_hex(&obj->oid));
	if (name)
		strbuf_addf(&buf, " (%s)", name);

	return buf.buf;
}