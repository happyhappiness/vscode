static int read_one_entry_quick(const unsigned char *sha1, struct strbuf *base,
				const char *pathname, unsigned mode, int stage,
				void *context)
{
	struct index_state *istate = context;
	return read_one_entry_opt(istate, sha1, base->buf, base->len, pathname,
				  mode, stage,
				  ADD_CACHE_JUST_APPEND);
}