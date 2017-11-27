static struct chain_head *
iptcc_find_chain_by_offset(TC_HANDLE_T handle, unsigned int offset)
{
	struct list_head *pos;

	if (list_empty(&handle->chains))
		return NULL;

	list_for_each(pos, &handle->chains) {
		struct chain_head *c = list_entry(pos, struct chain_head, list);
		if (offset >= c->head_offset && offset <= c->foot_offset)
			return c;
	}

	return NULL;
}