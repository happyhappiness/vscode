struct object *deref_tag(struct object *o, const char *warn, int warnlen)
{
	while (o && o->type == OBJ_TAG)
		if (((struct tag *)o)->tagged)
			o = parse_object(&((struct tag *)o)->tagged->oid);
		else
			o = NULL;
	if (!o && warn) {
		if (!warnlen)
			warnlen = strlen(warn);
		error("missing object referenced by '%.*s'", warnlen, warn);
	}
	return o;
}