static int read_one_entry(const unsigned char *sha1, struct strbuf *base,
			  const char *pathname, unsigned mode, int stage,
			  void *context)
{
	return read_one_entry_opt(sha1, base->buf, base->len, pathname,
				  mode, stage,
				  ADD_CACHE_OK_TO_ADD|ADD_CACHE_SKIP_DFCHECK);
}