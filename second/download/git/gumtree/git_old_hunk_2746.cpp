	strbuf_addbuf(buf, &mailnamebuf);
	strbuf_release(&mailnamebuf);
	fclose(mailname);
	return 0;
}

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

static void copy_email(const struct passwd *pw, struct strbuf *email)
{
	/*
	 * Make up a fake email address
	 * (name + '@' + hostname [+ '.' + domainname])
	 */
	strbuf_addstr(email, pw->pw_name);
	strbuf_addch(email, '@');

	if (!add_mailname_host(email))
		return;	/* read from "/etc/mailname" (Debian) */
	add_domainname(email);
}

const char *ident_default_name(void)
{
	if (!git_default_name.len) {
		copy_gecos(xgetpwuid_self(), &git_default_name);
		strbuf_trim(&git_default_name);
	}
	return git_default_name.buf;
}

const char *ident_default_email(void)
