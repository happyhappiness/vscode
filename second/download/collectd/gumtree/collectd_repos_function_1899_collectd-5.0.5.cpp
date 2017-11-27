static struct list_head *
iptcc_linearly_search_chain_index(const char *name, TC_HANDLE_T handle)
{
	unsigned int i=0;
	int res=0;

	struct list_head *list_pos;
	list_pos = &handle->chains;

	if (handle->chain_index_sz)
		list_pos = &handle->chain_index[0]->list;

	/* Linearly walk of chain index array */

	for (i=0; i < handle->chain_index_sz; i++) {
		if (handle->chain_index[i]) {
			res = strcmp(handle->chain_index[i]->name, name);
			if (res > 0)
				break; // One step too far
			list_pos = &handle->chain_index[i]->list;
			if (res == 0)
				break; // Direct hit
		}
	}

	return list_pos;
}