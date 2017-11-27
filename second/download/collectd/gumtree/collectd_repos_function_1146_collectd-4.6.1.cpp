static void __iptcc_p_add_chain(TC_HANDLE_T h, struct chain_head *c,
				unsigned int offset, unsigned int *num)
{
	struct list_head  *tail = h->chains.prev;
	struct chain_head *ctail;

	__iptcc_p_del_policy(h, *num);

	c->head_offset = offset;
	c->index = *num;

	/* Chains from kernel are already sorted, as they are inserted
	 * sorted. But there exists an issue when shifting to 1.4.0
	 * from an older version, as old versions allow last created
	 * chain to be unsorted.
	 */
	if (iptcc_is_builtin(c)) /* Only user defined chains are sorted*/
		list_add_tail(&c->list, &h->chains);
	else {
		ctail = list_entry(tail, struct chain_head, list);
		if (strcmp(c->name, ctail->name) > 0)
			list_add_tail(&c->list, &h->chains);/* Already sorted*/
		else
			iptc_insert_chain(h, c);/* Was not sorted */
	}

	h->chain_iterator_cur = c;
}