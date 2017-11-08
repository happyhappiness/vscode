static int get_name(const char *path, const struct object_id *oid, int flag, void *cb_data)
{
	int is_tag = starts_with(path, "refs/tags/");
	struct object_id peeled;
	int is_annotated, prio;

	/* Reject anything outside refs/tags/ unless --all */
	if (!all && !is_tag)
		return 0;

	/* Accept only tags that match the pattern, if given */
	if (pattern && (!is_tag || wildmatch(pattern, path + 10, 0, NULL)))
		return 0;

	/* Is it annotated? */
	if (!peel_ref(path, peeled.hash)) {
		is_annotated = !!oidcmp(oid, &peeled);
	} else {
		oidcpy(&peeled, oid);
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

	add_to_known_names(all ? path + 5 : path + 10, peeled.hash, prio, oid->hash);
	return 0;
}