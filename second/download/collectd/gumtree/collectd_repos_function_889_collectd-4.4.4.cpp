static inline void iptc_insert_chain(TC_HANDLE_T h, struct chain_head *c)
{
	struct chain_head *tmp;

	/* sort only user defined chains */
	if (!c->hooknum) {
		list_for_each_entry(tmp, &h->chains, list) {
			if (!tmp->hooknum && strcmp(c->name, tmp->name) <= 0) {
				list_add(&c->list, tmp->list.prev);
				return;
			}
		}
	}

	/* survived till end of list: add at tail */
	list_add_tail(&c->list, &h->chains);
}