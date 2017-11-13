static int mark_our_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *o = lookup_unknown_object(sha1);

	if (ref_is_hidden(refname)) {
		o->flags |= HIDDEN_REF;
		return 1;
	}
	if (!o)
		die("git upload-pack: cannot find object %s:", sha1_to_hex(sha1));
	o->flags |= OUR_REF;
	return 0;
}