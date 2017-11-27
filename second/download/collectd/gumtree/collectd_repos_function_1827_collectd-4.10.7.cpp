static void iptcc_chain_index_dump(TC_HANDLE_T h)
{
	unsigned int i = 0;

	/* Dump: contents of chain index array */
	for (i=0; i < h->chain_index_sz; i++) {
		if (h->chain_index[i]) {
			fprintf(stderr, "Chain index[%d].name: %s\n",
				i, h->chain_index[i]->name);
		}
	}
}