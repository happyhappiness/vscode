static int get_name(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	int is_tag = starts_with(path, "refs/tags/");
	unsigned char peeled[20];
	int is_annotated, prio;

	/* Reject anything outside refs/tags/ unless --all */
	if (!all && !is_tag)
		return 0;

	/* Accept only tags that match the pattern, if given */
	if (pattern && (!is_tag || wildmatch(pattern, path + 10, 0, NULL)))
		return 0;

	/* Is it annotated? */
	if (!peel_ref(path, peeled)) {
		is_annotated = !!hashcmp(sha1, peeled);
	} else {
		hashcpy(peeled, sha1);
		is_annotated = 0;
	}

	/*
	 * By default, we only use annotated tags, but with --tags
	 * we fall back to lightweight ones (even without --tags,
	 * we still remember lightweight ones, only to give hints
	 * in an error message).  --all allows any refs to be used.
	 */
	if (is_annotated)
		prio = 2;
	else if (is_tag)
		prio = 1;
	else
		prio = 0;

	add_to_known_names(all ? path + 5 : path + 10, peeled, prio, sha1);
	return 0;
}