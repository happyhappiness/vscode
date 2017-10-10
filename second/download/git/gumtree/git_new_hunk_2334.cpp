	char *s = shorten_unambiguous_ref(ref, 0);
	strbuf_reset(buf);
	strbuf_addstr(buf, s);
	free(s);
}

static int interpret_branch_mark(const char *name, int namelen,
				 int at, struct strbuf *buf,
				 int (*get_mark)(const char *, int),
				 const char *(*get_data)(struct branch *,
							 struct strbuf *))
{
	int len;
	struct branch *branch;
	struct strbuf err = STRBUF_INIT;
	const char *value;

	len = get_mark(name + at, namelen - at);
	if (!len)
		return -1;

	if (memchr(name, ':', at))
		return -1;

	if (at) {
		char *name_str = xmemdupz(name, at);
		branch = branch_get(name_str);
		free(name_str);
	} else
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
