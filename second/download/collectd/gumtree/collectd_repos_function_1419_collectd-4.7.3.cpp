const char *
TC_FIRST_CHAIN(TC_HANDLE_T *handle)
{
	struct chain_head *c = list_entry((*handle)->chains.next,
					  struct chain_head, list);

	iptc_fn = TC_FIRST_CHAIN;


	if (list_empty(&(*handle)->chains)) {
		DEBUGP(": no chains\n");
		return NULL;
	}

	(*handle)->chain_iterator_cur = c;
	iptcc_chain_iterator_advance(*handle);

	DEBUGP(": returning `%s'\n", c->name);
	return c->name;
}