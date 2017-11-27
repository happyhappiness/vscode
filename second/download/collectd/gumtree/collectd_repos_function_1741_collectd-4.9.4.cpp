static inline void iptc_insert_chain(TC_HANDLE_T h, struct chain_head *c)
{
	struct chain_head *tmp;
	struct list_head  *list_start_pos;
	unsigned int i=1;

	/* Find a smart place to start the insert search */
  	list_start_pos = iptcc_bsearch_chain_index(c->name, &i, h);

	/* Handle the case, where chain.name is smaller than index[0] */
	if (i==0 && strcmp(c->name, h->chain_index[0]->name) <= 0) {
		h->chain_index[0] = c; /* Update chain index head */
		list_start_pos = h->chains.next;
		debug("Update chain_index[0] with %s\n", c->name);
	}

	/* Handel if bsearch bails out early */
	if (list_start_pos == &h->chains) {
		list_start_pos = h->chains.next;
	}

	/* sort only user defined chains */
	if (!c->hooknum) {
		list_for_each_entry(tmp, list_start_pos->prev, list) {
			if (!tmp->hooknum && strcmp(c->name, tmp->name) <= 0) {
				list_add(&c->list, tmp->list.prev);
				return;
			}

			/* Stop if list head is reached */
			if (&tmp->list == &h->chains) {
				debug("Insert, list head reached add to tail\n");
				break;
			}
		}
	}

	/* survived till end of list: add at tail */
	list_add_tail(&c->list, &h->chains);
}