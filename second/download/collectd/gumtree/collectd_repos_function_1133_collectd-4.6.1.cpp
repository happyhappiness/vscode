static void iptcc_chain_index_free(TC_HANDLE_T h)
{
	h->chain_index_sz = 0;
	free(h->chain_index);
}