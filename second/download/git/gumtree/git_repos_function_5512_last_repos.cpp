static int fsck_handle_ref(const char *refname, const struct object_id *oid,
			   int flag, void *cb_data)
{
	struct object *obj;

	obj = parse_object(oid);
	if (!obj) {
		error("%s: invalid sha1 pointer %s", refname, oid_to_hex(oid));
		errors_found |= ERROR_REACHABLE;
		/* We'll continue with the rest despite the error.. */
		return 0;
	}
	if (obj->type != OBJ_COMMIT && is_branch(refname)) {
		error("%s: not a commit", refname);
		errors_found |= ERROR_REFS;
	}
	default_refs++;
	obj->flags |= USED;
	if (name_objects)
		add_decoration(fsck_walk_options.object_names,
			obj, xstrdup(refname));
	mark_object_reachable(obj);

	return 0;
}