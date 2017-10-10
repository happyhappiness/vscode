	strbuf_addbuf(buf, &mailnamebuf);
	strbuf_release(&mailnamebuf);
	fclose(mailname);
	return 0;
}

static int canonical_name(const char *host, struct strbuf *out)
{
	int status = -1;

#ifndef NO_IPV6
	struct addrinfo hints, *ai;
	memset (&hints, '\0', sizeof (hints));
	hints.ai_flags = AI_CANONNAME;
	if (!getaddrinfo(host, NULL, &hints, &ai)) {
		if (ai && strchr(ai->ai_canonname, '.')) {
			strbuf_addstr(out, ai->ai_canonname);
			status = 0;
		}
		freeaddrinfo(ai);
	}
#else
	struct hostent *he = gethostbyname(host);
	if (he && strchr(he->h_name, '.')) {
		strbuf_addstr(out, he->h_name);
		status = 0;
	}
#endif /* NO_IPV6 */

	return status;
}

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

static void copy_email(const struct passwd *pw, struct strbuf *email,
		       int *is_bogus)
{
	/*
	 * Make up a fake email address
	 * (name + '@' + hostname [+ '.' + domainname])
	 */
	strbuf_addstr(email, pw->pw_name);
	strbuf_addch(email, '@');

	if (!add_mailname_host(email))
		return;	/* read from "/etc/mailname" (Debian) */
	add_domainname(email, is_bogus);
}

const char *ident_default_name(void)
{
	if (!git_default_name.len) {
		copy_gecos(xgetpwuid_self(&default_name_is_bogus), &git_default_name);
		strbuf_trim(&git_default_name);
	}
	return git_default_name.buf;
}

const char *ident_default_email(void)
