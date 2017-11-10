static enum contains_result contains_test(struct commit *candidate,
			    const struct commit_list *want)
{
	/* was it previously marked as containing a want commit? */
	if (candidate->object.flags & TMP_MARK)
		return 1;
	/* or marked as not possibly containing a want commit? */
	if (candidate->object.flags & UNINTERESTING)
		return 0;
	/* or are we it? */
	if (in_commit_list(want, candidate)) {
		candidate->object.flags |= TMP_MARK;
		return 1;
	}

	if (parse_commit(candidate) < 0)
		return 0;

	return -1;
}