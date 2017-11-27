int TC_IS_CHAIN(const char *chain, const TC_HANDLE_T handle)
{
	iptc_fn = TC_IS_CHAIN;
	return iptcc_find_label(chain, handle) != NULL;
}