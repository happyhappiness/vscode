static int rev_list_insert_ref(const char *refname, const unsigned char *sha1)
{
	struct object *o = deref_tag(parse_object(sha1), refname, 0);

	if (o && o->type == OBJ_COMMIT)
		rev_list_push((struct commit *)o, SEEN);

	return 0;
}