struct object *deref_tag_noverify(struct object *o)
{
	while (o && o->type == OBJ_TAG) {
		o = parse_object(&o->oid);
		if (o && o->type == OBJ_TAG && ((struct tag *)o)->tagged)
			o = ((struct tag *)o)->tagged;
		else
			o = NULL;
	}
	return o;
}