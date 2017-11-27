static int __iptcc_p_del_policy(TC_HANDLE_T h, unsigned int num)
{
	const unsigned char *data;

	if (h->chain_iterator_cur) {
		/* policy rule is last rule */
		struct rule_head *pr = (struct rule_head *)
			h->chain_iterator_cur->rules.prev;

		/* save verdict */
		data = GET_TARGET(pr->entry)->data;
		h->chain_iterator_cur->verdict = *(const int *)data;

		/* save counter and counter_map information */
		h->chain_iterator_cur->counter_map.maptype = 
						COUNTER_MAP_NORMAL_MAP;
		h->chain_iterator_cur->counter_map.mappos = num-1;
		memcpy(&h->chain_iterator_cur->counters, &pr->entry->counters, 
			sizeof(h->chain_iterator_cur->counters));

		/* foot_offset points to verdict rule */
		h->chain_iterator_cur->foot_index = num;
		h->chain_iterator_cur->foot_offset = pr->offset;

		/* delete rule from cache */
		iptcc_delete_rule(pr);
		h->chain_iterator_cur->num_rules--;

		return 1;
	}
	return 0;
}