		print_line(extra);
	parse_credential_file(fn, c, NULL, print_line);
	if (commit_lock_file(&credential_lock) < 0)
		die_errno("unable to commit credential store");
}

static void store_credential_file(const char *fn, struct credential *c)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "%s://", c->protocol);
	strbuf_addstr_urlencode(&buf, c->username, 1);
	strbuf_addch(&buf, ':');
	strbuf_addstr_urlencode(&buf, c->password, 1);
	strbuf_addch(&buf, '@');
	if (c->host)
