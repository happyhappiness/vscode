	if (obj->type != OBJ_COMMIT && is_branch(refname)) {
		error("%s: not a commit", refname);
		errors_found |= ERROR_REFS;
	}
	default_refs++;
	obj->used = 1;
	mark_object_reachable(obj);

	return 0;
}

static void get_default_heads(void)
