static int iptcc_chain_index_build(TC_HANDLE_T h)
{
	unsigned int list_length = CHAIN_INDEX_BUCKET_LEN;
	unsigned int chains = 0;
	unsigned int cindex = 0;
	struct chain_head *c;

	/* Build up the chain index array here */
	debug("Building chain index\n");

	debug("Number of user defined chains:%d bucket_sz:%d array_sz:%d\n",
		h->num_chains, list_length, h->chain_index_sz);

	if (h->chain_index_sz == 0)
		return 0;

	list_for_each_entry(c, &h->chains, list) {

		/* Issue: The index array needs to start after the
		 * builtin chains, as they are not sorted */
		if (!iptcc_is_builtin(c)) {
			cindex=chains / list_length;

			/* Safe guard, break out on array limit, this
			 * is useful if chains are added and array is
			 * rebuild, without realloc of memory. */
			if (cindex >= h->chain_index_sz)
				break;

			if ((chains % list_length)== 0) {
				debug("\nIndex[%d] Chains:", cindex);
				h->chain_index[cindex] = c;
			}
			chains++;
		}
		debug("%s, ", c->name);
	}
	debug("\n");

	return 1;
}