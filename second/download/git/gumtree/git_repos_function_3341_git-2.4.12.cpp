static int interpret_upstream_mark(const char *name, int namelen,
				   int at, struct strbuf *buf)
{
	int len;

	len = upstream_mark(name + at, namelen - at);
	if (!len)
		return -1;

	if (memchr(name, ':', at))
		return -1;

	set_shortened_ref(buf, get_upstream_branch(name, at));
	return len + at;
}