		branch = branch_get(NULL);

	value = get_data(branch, &err);
	if (!value)
		die("%s", err.buf);

	if (!branch_interpret_allowed(value, allowed))
		return -1;

	set_shortened_ref(buf, value);
	return len + at;
}

int interpret_branch_name(const char *name, int namelen, struct strbuf *buf,
			  unsigned allowed)
{
	char *at;
	const char *start;
	int len;

	if (!namelen)
		namelen = strlen(name);

	if (!allowed || (allowed & INTERPRET_BRANCH_LOCAL)) {
		len = interpret_nth_prior_checkout(name, namelen, buf);
		if (!len) {
			return len; /* syntax Ok, not enough switches */
		} else if (len > 0) {
			if (len == namelen)
				return len; /* consumed all */
			else
				return reinterpret(name, namelen, len, buf, allowed);
		}
	}

	for (start = name;
	     (at = memchr(start, '@', namelen - (start - name)));
	     start = at + 1) {

		if (!allowed || (allowed & INTERPRET_BRANCH_HEAD)) {
			len = interpret_empty_at(name, namelen, at - name, buf);
			if (len > 0)
				return reinterpret(name, namelen, len, buf,
						   allowed);
		}

		len = interpret_branch_mark(name, namelen, at - name, buf,
					    upstream_mark, branch_get_upstream,
					    allowed);
		if (len > 0)
			return len;

		len = interpret_branch_mark(name, namelen, at - name, buf,
					    push_mark, branch_get_push,
					    allowed);
		if (len > 0)
			return len;
	}

	return -1;
}

void strbuf_branchname(struct strbuf *sb, const char *name, unsigned allowed)
{
	int len = strlen(name);
	int used = interpret_branch_name(name, len, sb, allowed);

	if (used < 0)
		used = 0;
	strbuf_add(sb, name + used, len - used);
}

int strbuf_check_branch_ref(struct strbuf *sb, const char *name)
{
	strbuf_branchname(sb, name, INTERPRET_BRANCH_LOCAL);
	if (name[0] == '-')
		return -1;
	strbuf_splice(sb, 0, 0, "refs/heads/", 11);
	return check_refname_format(sb->buf, 0);
}

