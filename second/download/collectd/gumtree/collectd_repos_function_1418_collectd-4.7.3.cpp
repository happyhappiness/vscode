static void iptcc_chain_iterator_advance(TC_HANDLE_T handle)
{
	struct chain_head *c = handle->chain_iterator_cur;

	if (c->list.next == &handle->chains)
		handle->chain_iterator_cur = NULL;
	else
		handle->chain_iterator_cur = 
			list_entry(c->list.next, struct chain_head, list);
}