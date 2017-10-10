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
	obj->used = 1;
	mark_object_reachable(obj);

	return 0;
}
