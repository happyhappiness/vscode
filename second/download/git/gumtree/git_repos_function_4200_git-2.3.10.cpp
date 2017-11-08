static int exclude_existing(const char *match)
{
	static struct string_list existing_refs = STRING_LIST_INIT_DUP;
	char buf[1024];
	int matchlen = match ? strlen(match) : 0;

	for_each_ref(add_existing, &existing_refs);
	while (fgets(buf, sizeof(buf), stdin)) {
		char *ref;
		int len = strlen(buf);

		if (len > 0 && buf[len - 1] == '\n')
			buf[--len] = '\0';
		if (3 <= len && !strcmp(buf + len - 3, "^{}")) {
			len -= 3;
			buf[len] = '\0';
		}
		for (ref = buf + len; buf < ref; ref--)
			if (isspace(ref[-1]))
				break;
		if (match) {
			int reflen = buf + len - ref;
			if (reflen < matchlen)
				continue;
			if (strncmp(ref, match, matchlen))
				continue;
		}
		if (check_refname_format(ref, 0)) {
			warning("ref '%s' ignored", ref);
			continue;
		}
		if (!string_list_has_string(&existing_refs, ref)) {
			printf("%s\n", buf);
		}
	}
	return 0;
}