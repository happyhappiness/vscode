int
TC_BUILTIN(const char *chain, const TC_HANDLE_T handle)
{
	struct chain_head *c;
	
	iptc_fn = TC_BUILTIN;

	c = iptcc_find_label(chain, handle);
	if (!c) {
		errno = ENOENT;
		return 0;
	}

	return iptcc_is_builtin(c);
}