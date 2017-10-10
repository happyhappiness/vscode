
	return !clean;
}

static int is_index_unchanged(void)
{
	struct object_id head_oid;
	struct commit *head_commit;

	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_oid.hash, NULL))
		return error(_("could not resolve HEAD commit\n"));

	head_commit = lookup_commit(&head_oid);

	/*
	 * If head_commit is NULL, check_commit, called from
	 * lookup_commit, would have indicated that head_commit is not
	 * a commit object already.  parse_commit() will return failure
	 * without further complaints in such a case.  Otherwise, if
