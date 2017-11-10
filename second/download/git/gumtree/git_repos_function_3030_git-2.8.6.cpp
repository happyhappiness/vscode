static int check_ancestors(const char *prefix)
{
	struct rev_info revs;
	struct object_array pending_copy;
	int res;

	bisect_rev_setup(&revs, prefix, "^%s", "%s", 0);

	/* Save pending objects, so they can be cleaned up later. */
	pending_copy = revs.pending;
	revs.leak_pending = 1;

	/*
	 * bisect_common calls prepare_revision_walk right away, which
	 * (together with .leak_pending = 1) makes us the sole owner of
	 * the list of pending objects.
	 */
	bisect_common(&revs);
	res = (revs.commits != NULL);

	/* Clean up objects used, as they will be reused. */
	clear_commit_marks_for_object_array(&pending_copy, ALL_REV_FLAGS);
	free(pending_copy.objects);

	return res;
}