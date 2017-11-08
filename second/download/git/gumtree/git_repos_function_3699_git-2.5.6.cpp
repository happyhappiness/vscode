static void add_domainname(struct strbuf *out)
{
	char buf[1024];
	struct hostent *he;

	if (gethostname(buf, sizeof(buf))) {
		warning("cannot get host name: %s", strerror(errno));
		strbuf_addstr(out, "(none)");
		return;
	}
	if (strchr(buf, '.'))
		strbuf_addstr(out, buf);
	else if ((he = gethostbyname(buf)) && strchr(he->h_name, '.'))
		strbuf_addstr(out, he->h_name);
	else
		strbuf_addf(out, "%s.(none)", buf);
}