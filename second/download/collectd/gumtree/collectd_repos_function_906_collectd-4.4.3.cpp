const char *
TC_NEXT_CHAIN(TC_HANDLE_T *handle)
{
	struct chain_head *c = (*handle)->chain_iterator_cur;

	iptc_fn = TC_NEXT_CHAIN;

	if (!c) {
		DEBUGP(": no more chains\n");
		return NULL;
	}

	iptcc_chain_iterator_advance(*handle);
	
	DEBUGP(": returning `%s'\n", c->name);
	return c->name;
}