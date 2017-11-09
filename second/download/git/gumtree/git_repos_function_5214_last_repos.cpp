static int show_ref(const char *refname, const struct object_id *oid,
		    int flag, void *cbdata)
{
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
			if (refname[reflen - len - 1] == '/')
				goto match;
		}
		return 0;
	}

match:
	found_match++;

	show_one(refname, oid);

	return 0;
}