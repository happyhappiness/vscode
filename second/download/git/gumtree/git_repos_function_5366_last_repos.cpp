static void construct_fullname(struct strbuf *out, const struct repository *repo,
			       const struct cache_entry *ce)
{
	strbuf_reset(out);
	if (repo->submodule_prefix)
		strbuf_addstr(out, repo->submodule_prefix);
	strbuf_addstr(out, ce->name);
}