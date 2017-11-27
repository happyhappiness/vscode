static int iptcc_chain_index_delete_chain(struct chain_head *c, TC_HANDLE_T h)
{
	struct list_head *index_ptr, *index_ptr2, *next;
	struct chain_head *c2;
	unsigned int idx, idx2;

	index_ptr = iptcc_bsearch_chain_index(c->name, &idx, h);

	debug("Del chain[%s] c->list:%p index_ptr:%p\n",
	      c->name, &c->list, index_ptr);

	/* Save the next pointer */
	next = c->list.next;
	list_del(&c->list);

	if (index_ptr == &c->list) { /* Chain used as index ptr */

		/* See if its possible to avoid a rebuild, by shifting
		 * to next pointer.  Its possible if the next pointer
		 * is located in the same index bucket.
		 */
		c2         = list_entry(next, struct chain_head, list);
		index_ptr2 = iptcc_bsearch_chain_index(c2->name, &idx2, h);
		if (idx != idx2) {
			/* Rebuild needed */
			return iptcc_chain_index_rebuild(h);
		} else {
			/* Avoiding rebuild */
			debug("Update cindex[%d] with next ptr name:[%s]\n",
			      idx, c2->name);
			h->chain_index[idx]=c2;
			return 0;
		}
	}
	return 0;
}