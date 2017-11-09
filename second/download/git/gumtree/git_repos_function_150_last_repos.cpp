static int is_our_ref(struct object *o)
{
	int allow_hidden_ref = (allow_unadvertised_object_request &
			(ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1));
	return o->flags & ((allow_hidden_ref ? HIDDEN_REF : 0) | OUR_REF);
}