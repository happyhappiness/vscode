static char *guess_ref(const char *name, struct ref *peer)
{
	struct strbuf buf = STRBUF_INIT;
	unsigned char sha1[20];

	const char *r = resolve_ref_unsafe(peer->name, RESOLVE_REF_READING,
					   sha1, NULL);
	if (!r)
		return NULL;

	if (starts_with(r, "refs/heads/"))
		strbuf_addstr(&buf, "refs/heads/");
	else if (starts_with(r, "refs/tags/"))
		strbuf_addstr(&buf, "refs/tags/");
	else
		return NULL;

	strbuf_addstr(&buf, name);
	return strbuf_detach(&buf, NULL);
}