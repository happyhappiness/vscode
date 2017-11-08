static int clear_marks(const char *refname, const struct object_id *oid,
		       int flag, void *cb_data)
{
	struct object *o = deref_tag(parse_object(oid->hash), refname, 0);

	if (o && o->type == OBJ_COMMIT)
		clear_commit_marks((struct commit *)o,
				   COMMON | COMMON_REF | SEEN | POPPED);
	return 0;
}