static int append_matching_ref(const char *refname, const struct object_id *oid,
			       int flag, void *cb_data)
{
	/* we want to allow pattern hold/<asterisk> to show all
	 * branches under refs/heads/hold/, and v0.99.9? to show
	 * refs/tags/v0.99.9a and friends.
	 */
	const char *tail;
	int slash = count_slashes(refname);
	for (tail = refname; *tail && match_ref_slash < slash; )
		if (*tail++ == '/')
			slash--;
	if (!*tail)
		return 0;
	if (wildmatch(match_ref_pattern, tail, 0))
		return 0;
	if (starts_with(refname, "refs/heads/"))
		return append_head_ref(refname, oid, flag, cb_data);
	if (starts_with(refname, "refs/tags/"))
		return append_tag_ref(refname, oid, flag, cb_data);
	return append_ref(refname, oid, 0);
}