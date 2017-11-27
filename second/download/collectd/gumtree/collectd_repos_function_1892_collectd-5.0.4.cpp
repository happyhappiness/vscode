static int iptcc_chain_index_alloc(TC_HANDLE_T h)
{
	unsigned int list_length = CHAIN_INDEX_BUCKET_LEN;
	unsigned int array_elems;
	unsigned int array_mem;

	/* Allocate memory for the chain index array */
	array_elems = (h->num_chains / list_length) +
                      (h->num_chains % list_length ? 1 : 0);
	array_mem   = sizeof(h->chain_index) * array_elems;

	debug("Alloc Chain index, elems:%d mem:%d bytes\n",
	      array_elems, array_mem);

	h->chain_index = malloc(array_mem);
	if (!h->chain_index) {
		h->chain_index_sz = 0;
		return -ENOMEM;
	}
	memset(h->chain_index, 0, array_mem);
	h->chain_index_sz = array_elems;

	return 1;
}