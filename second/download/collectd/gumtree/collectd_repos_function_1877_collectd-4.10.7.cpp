int
TC_CREATE_CHAIN(const IPT_CHAINLABEL chain, TC_HANDLE_T *handle)
{
	static struct chain_head *c;
	int capacity;
	int exceeded;

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
	(*handle)->num_chains++; /* New user defined chain */

	DEBUGP("Creating chain `%s'\n", chain);
	iptc_insert_chain(*handle, c); /* Insert sorted */

	/* Inserting chains don't change the correctness of the chain
	 * index (except if its smaller than index[0], but that
	 * handled by iptc_insert_chain).  It only causes longer lists
	 * in the buckets. Thus, only rebuild chain index when the
	 * capacity is exceed with CHAIN_INDEX_INSERT_MAX chains.
	 */
	capacity = (*handle)->chain_index_sz * CHAIN_INDEX_BUCKET_LEN;
	exceeded = ((((*handle)->num_chains)-capacity));
	if (exceeded > CHAIN_INDEX_INSERT_MAX) {
		debug("Capacity(%d) exceeded(%d) rebuild (chains:%d)\n",
		      capacity, exceeded, (*handle)->num_chains);
		iptcc_chain_index_rebuild(*handle);
	}

	set_changed(*handle);

	return 1;
}