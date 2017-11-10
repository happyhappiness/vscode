struct commit *get_merge_parent(const char *name)
{
	struct object *obj;
	struct commit *commit;
	struct object_id oid;
	if (get_sha1(name, oid.hash))
		return NULL;
	obj = parse_object(oid.hash);
	commit = (struct commit *)peel_to_type(name, 0, obj, OBJ_COMMIT);
	if (commit && !commit->util)
		set_merge_remote_desc(commit, name, obj);
	return commit;
}