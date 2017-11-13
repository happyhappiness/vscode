static void add_domainname(struct strbuf *out, int *is_bogus)
{
	char buf[1024];

	if (gethostname(buf, sizeof(buf))) {
		warning("cannot get host name: %s", strerror(errno));
		strbuf_addstr(out, "(none)");
		*is_bogus = 1;
		return;
	}
	if (strchr(buf, '.'))
		strbuf_addstr(out, buf);
	else if (canonical_name(buf, out) < 0) {
		strbuf_addf(out, "%s.(none)", buf);
		*is_bogus = 1;
	}
}