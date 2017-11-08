static int mark_our_ref(const char *refname, const struct object_id *oid)
{
	struct object *o = lookup_unknown_object(oid->hash);

	if (ref_is_hidden(refname)) {
		o->flags |= HIDDEN_REF;
		return 1;
	}
	o->flags |= OUR_REF;
	return 0;
}