struct commit *lookup_commit_reference_gently(const struct object_id *oid,
					      int quiet)
{
	struct object *obj = deref_tag(parse_object(oid), NULL, 0);

	if (!obj)
		return NULL;
	return object_as_type(obj, OBJ_COMMIT, quiet);
}