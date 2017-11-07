static int fsck_handle_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *obj;

	obj = parse_object(sha1);
	if (!obj) {
		error("%s: invalid sha1 pointer %s", refname, sha1_to_hex(sha1));
		errors_found |= ERROR_REACHABLE;
		/* We'll continue with the rest despite the error.. */
		return 0;
	}
	if (obj->type != OBJ_COMMIT && is_branch(refname))
		error("%s: not a commit", refname);
	default_refs++;
	obj->used = 1;
	mark_object_reachable(obj);

	return 0;
}