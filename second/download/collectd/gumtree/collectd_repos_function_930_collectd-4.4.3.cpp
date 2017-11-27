int
TC_CREATE_CHAIN(const IPT_CHAINLABEL chain, TC_HANDLE_T *handle)
{
	static struct chain_head *c;

	iptc_fn = TC_CREATE_CHAIN;

	/* find_label doesn't cover built-in targets: DROP, ACCEPT,
           QUEUE, RETURN. */
	if (iptcc_find_label(chain, *handle)
	    || strcmp(chain, LABEL_DROP) == 0
	    || strcmp(chain, LABEL_ACCEPT) == 0
	    || strcmp(chain, LABEL_QUEUE) == 0
	    || strcmp(chain, LABEL_RETURN) == 0) {
		DEBUGP("Chain `%s' already exists\n", chain);
		errno = EEXIST;
		return 0;
	}

	if (strlen(chain)+1 > sizeof(IPT_CHAINLABEL)) {
		DEBUGP("Chain name `%s' too long\n", chain);
		errno = EINVAL;
		return 0;
	}

	c = iptcc_alloc_chain_head(chain, 0);
	if (!c) {
		DEBUGP("Cannot allocate memory for chain `%s'\n", chain);
		errno = ENOMEM;
		return 0;

	}

	DEBUGP("Creating chain `%s'\n", chain);
	iptc_insert_chain(*handle, c); /* Insert sorted */

	set_changed(*handle);

	return 1;
}