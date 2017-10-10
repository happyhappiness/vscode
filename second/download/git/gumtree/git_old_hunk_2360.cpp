		print_line(extra);
	parse_credential_file(fn, c, NULL, print_line);
	if (commit_lock_file(&credential_lock) < 0)
		die_errno("unable to commit credential store");
}

static void store_credential(const char *fn, struct credential *c)
{
	struct strbuf buf = STRBUF_INIT;

	/*
	 * Sanity check that what we are storing is actually sensible.
	 * In particular, we can't make a URL without a protocol field.
	 * Without either a host or pathname (depending on the scheme),
	 * we have no primary key. And without a username and password,
	 * we are not actually storing a credential.
	 */
	if (!c->protocol || !(c->host || c->path) ||
	    !c->username || !c->password)
		return;

	strbuf_addf(&buf, "%s://", c->protocol);
	strbuf_addstr_urlencode(&buf, c->username, 1);
	strbuf_addch(&buf, ':');
	strbuf_addstr_urlencode(&buf, c->password, 1);
	strbuf_addch(&buf, '@');
	if (c->host)
