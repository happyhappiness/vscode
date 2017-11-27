static struct chain_head *
iptcc_find_label(const char *name, TC_HANDLE_T handle)
{
	struct list_head *pos;

	if (list_empty(&handle->chains))
		return NULL;

	list_for_each(pos, &handle->chains) {
		struct chain_head *c = list_entry(pos, struct chain_head, list);
		if (!strcmp(c->name, name))
			return c;
	}

	return NULL;
}