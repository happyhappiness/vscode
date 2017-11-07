static int contains_recurse(struct commit *candidate,
			    const struct commit_list *want)
{
	struct commit_list *p;

	/* was it previously marked as containing a want commit? */
	if (candidate->object.flags & TMP_MARK)
		return 1;
	/* or marked as not possibly containing a want commit? */
	if (candidate->object.flags & UNINTERESTING)
		return 0;
	/* or are we it? */
	if (in_commit_list(want, candidate))
		return 1;

	if (parse_commit(candidate) < 0)
		return 0;

	/* Otherwise recurse and mark ourselves for future traversals. */
	for (p = candidate->parents; p; p = p->next) {
		if (contains_recurse(p->item, want)) {
			candidate->object.flags |= TMP_MARK;
			return 1;
		}
	}
	candidate->object.flags |= UNINTERESTING;
	return 0;
}