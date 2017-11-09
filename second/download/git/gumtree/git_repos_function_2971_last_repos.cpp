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
	 * the commit is invalid, parse_commit() will complain.  So
	 * there is nothing for us to say here.  Just return failure.
	 */
	if (parse_commit(head_commit))
		return -1;

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree))
		if (cache_tree_update(&the_index, 0))
			return error(_("unable to update cache tree\n"));

	return !oidcmp(&active_cache_tree->oid,
		       &head_commit->tree->object.oid);
}