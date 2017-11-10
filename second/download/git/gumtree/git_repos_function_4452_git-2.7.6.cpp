static int show_ref(const char *refname, const struct object_id *oid,
		    int flag, void *cbdata)
{
	const char *hex;
	struct object_id peeled;

	if (show_head && !strcmp(refname, "HEAD"))
		goto match;

	if (tags_only || heads_only) {
		int match;

		match = heads_only && starts_with(refname, "refs/heads/");
		match |= tags_only && starts_with(refname, "refs/tags/");
		if (!match)
			return 0;
	}
	if (pattern) {
		int reflen = strlen(refname);
		const char **p = pattern, *m;
		while ((m = *p++) != NULL) {
			int len = strlen(m);
			if (len > reflen)
				continue;
			if (memcmp(m, refname + reflen - len, len))
				continue;
			if (len == reflen)
				goto match;
			/* "--verify" requires an exact match */
			if (verify)
				continue;
			if (refname[reflen - len - 1] == '/')
				goto match;
		}
		return 0;
	}

match:
	found_match++;

	/* This changes the semantics slightly that even under quiet we
	 * detect and return error if the repository is corrupt and
	 * ref points at a nonexistent object.
	 */
	if (!has_sha1_file(oid->hash))
		die("git show-ref: bad ref %s (%s)", refname,
		    oid_to_hex(oid));

	if (quiet)
		return 0;

	show_one(refname, oid);

	if (!deref_tags)
		return 0;

	if (!peel_ref(refname, peeled.hash)) {
		hex = find_unique_abbrev(peeled.hash, abbrev);
		printf("%s %s^{}\n", hex, refname);
	}
	return 0;
}