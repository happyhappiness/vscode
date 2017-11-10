void notes_cache_init(struct notes_cache *c, const char *name,
		     const char *validity)
{
	struct strbuf ref = STRBUF_INIT;
	int flags = NOTES_INIT_WRITABLE;

	memset(c, 0, sizeof(*c));
	c->validity = xstrdup(validity);

	strbuf_addf(&ref, "refs/notes/%s", name);
	if (!notes_cache_match_validity(ref.buf, validity))
		flags |= NOTES_INIT_EMPTY;
	init_notes(&c->tree, ref.buf, combine_notes_overwrite, flags);
	strbuf_release(&ref);
}