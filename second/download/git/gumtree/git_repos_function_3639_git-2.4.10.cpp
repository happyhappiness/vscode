static int clear_marks(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *o = deref_tag(parse_object(sha1), refname, 0);

	if (o && o->type == OBJ_COMMIT)
		clear_commit_marks((struct commit *)o,
				   COMMON | COMMON_REF | SEEN | POPPED);
	return 0;
}