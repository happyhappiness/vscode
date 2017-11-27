int
TC_DELETE_CHAIN(const IPT_CHAINLABEL chain, TC_HANDLE_T *handle)
{
	unsigned int references;
	struct chain_head *c;

	iptc_fn = TC_DELETE_CHAIN;

	if (!(c = iptcc_find_label(chain, *handle))) {
		DEBUGP("cannot find chain `%s'\n", chain);
		errno = ENOENT;
		return 0;
	}

	if (TC_BUILTIN(chain, *handle)) {
		DEBUGP("cannot remove builtin chain `%s'\n", chain);
		errno = EINVAL;
		return 0;
	}

	if (!TC_GET_REFERENCES(&references, chain, handle)) {
		DEBUGP("cannot get references on chain `%s'\n", chain);
		return 0;
	}

	if (references > 0) {
		DEBUGP("chain `%s' still has references\n", chain);
		errno = EMLINK;
		return 0;
	}

	if (c->num_rules) {
		DEBUGP("chain `%s' is not empty\n", chain);
		errno = ENOTEMPTY;
		return 0;
	}

	/* If we are about to delete the chain that is the current
	 * iterator, move chain iterator firward. */
	if (c == (*handle)->chain_iterator_cur)
		iptcc_chain_iterator_advance(*handle);

	list_del(&c->list);
	free(c);

	DEBUGP("chain `%s' deleted\n", chain);

	set_changed(*handle);

	return 1;
}