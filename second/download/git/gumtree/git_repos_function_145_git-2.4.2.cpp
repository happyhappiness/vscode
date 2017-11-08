static int is_our_ref(struct object *o)
{
	return o->flags &
		((allow_tip_sha1_in_want ? HIDDEN_REF : 0) | OUR_REF);
}