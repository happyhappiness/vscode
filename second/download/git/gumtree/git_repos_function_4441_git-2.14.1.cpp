static char *guess_ref(const char *name, struct ref *peer)
{
	struct strbuf buf = STRBUF_INIT;
	struct object_id oid;

	const char *r = resolve_ref_unsafe(peer->name, RESOLVE_REF_READING,
					   oid.hash, NULL);
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