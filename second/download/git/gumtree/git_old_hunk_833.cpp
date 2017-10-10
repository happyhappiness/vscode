		branch = branch_get(NULL);

	value = get_data(branch, &err);
	if (!value)
		die("%s", err.buf);

	set_shortened_ref(buf, value);
	return len + at;
}

/*
 * This reads short-hand syntax that not only evaluates to a commit
 * object name, but also can act as if the end user spelled the name
 * of the branch from the command line.
 *
 * - "@{-N}" finds the name of the Nth previous branch we were on, and
 *   places the name of the branch in the given buf and returns the
 *   number of characters parsed if successful.
 *
 * - "<branch>@{upstream}" finds the name of the other ref that
 *   <branch> is configured to merge with (missing <branch> defaults
 *   to the current branch), and places the name of the branch in the
 *   given buf and returns the number of characters parsed if
 *   successful.
 *
 * If the input is not of the accepted format, it returns a negative
 * number to signal an error.
 *
 * If the input was ok but there are not N branch switches in the
 * reflog, it returns 0.
 */
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

		len = interpret_branch_mark(name, namelen, at - name, buf,
					    upstream_mark, branch_get_upstream);
		if (len > 0)
			return len;

		len = interpret_branch_mark(name, namelen, at - name, buf,
					    push_mark, branch_get_push);
		if (len > 0)
			return len;
	}

	return -1;
}

int strbuf_branchname(struct strbuf *sb, const char *name)
{
	int len = strlen(name);
	int used = interpret_branch_name(name, len, sb);

	if (used == len)
		return 0;
	if (used < 0)
		used = 0;
	strbuf_add(sb, name + used, len - used);
	return len;
}

int strbuf_check_branch_ref(struct strbuf *sb, const char *name)
{
	strbuf_branchname(sb, name);
	if (name[0] == '-')
		return -1;
	strbuf_splice(sb, 0, 0, "refs/heads/", 11);
	return check_refname_format(sb->buf, 0);
}

