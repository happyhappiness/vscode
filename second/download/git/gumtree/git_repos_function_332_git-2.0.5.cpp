static void credential_describe(struct credential *c, struct strbuf *out)
{
	if (!c->protocol)
		return;
	strbuf_addf(out, "%s://", c->protocol);
	if (c->username && *c->username)
		strbuf_addf(out, "%s@", c->username);
	if (c->host)
		strbuf_addstr(out, c->host);
	if (c->path)
		strbuf_addf(out, "/%s", c->path);
}