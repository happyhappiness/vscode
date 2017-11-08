int interpret_branch_name(const char *name, int namelen, struct strbuf *buf)
{
	char *at;
	const char *start;
	int len = interpret_nth_prior_checkout(name, namelen, buf);

	if (!namelen)
		namelen = strlen(name);

	if (!len) {
		return len; /* syntax Ok, not enough switches */
	} else if (len > 0) {
		if (len == namelen)
			return len; /* consumed all */
		else
			return reinterpret(name, namelen, len, buf);
	}

	for (start = name;
	     (at = memchr(start, '@', namelen - (start - name)));
	     start = at + 1) {

		len = interpret_empty_at(name, namelen, at - name, buf);
		if (len > 0)
			return reinterpret(name, namelen, len, buf);

		len = interpret_upstream_mark(name, namelen, at - name, buf);
		if (len > 0)
			return len;
	}

	return -1;
}