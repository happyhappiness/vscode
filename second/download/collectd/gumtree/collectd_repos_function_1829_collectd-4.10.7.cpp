static int iptcc_chain_index_rebuild(TC_HANDLE_T h)
{
	debug("REBUILD chain index array\n");
	iptcc_chain_index_free(h);
	if ((iptcc_chain_index_alloc(h)) < 0)
		return -ENOMEM;
	iptcc_chain_index_build(h);
	return 1;
}