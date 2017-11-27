int
TC_DELETE_ENTRY(const IPT_CHAINLABEL chain,
		const STRUCT_ENTRY *origfw,
		unsigned char *matchmask,
		TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r, *i;

	iptc_fn = TC_DELETE_ENTRY;
	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	/* Create a rule_head from origfw. */
	r = iptcc_alloc_rule(c, origfw->next_offset);
	if (!r) {
		errno = ENOMEM;
		return 0;
	}

	memcpy(r->entry, origfw, origfw->next_offset);
	r->counter_map.maptype = COUNTER_MAP_NOMAP;
	if (!iptcc_map_target(*handle, r)) {
		DEBUGP("unable to map target of rule for chain `%s'\n", chain);
		free(r);
		return 0;
	} else {
		/* iptcc_map_target increment target chain references
		 * since this is a fake rule only used for matching
		 * the chain references count is decremented again. 
		 */
		if (r->type == IPTCC_R_JUMP
		    && r->jump)
			r->jump->references--;
	}

	list_for_each_entry(i, &c->rules, list) {
		unsigned char *mask;

		mask = is_same(r->entry, i->entry, matchmask);
		if (!mask)
			continue;

		if (!target_same(r, i, mask))
			continue;

		/* If we are about to delete the rule that is the
		 * current iterator, move rule iterator back.  next
		 * pointer will then point to real next node */
		if (i == (*handle)->rule_iterator_cur) {
			(*handle)->rule_iterator_cur = 
				list_entry((*handle)->rule_iterator_cur->list.prev,
					   struct rule_head, list);
		}

		c->num_rules--;
		iptcc_delete_rule(i);

		set_changed(*handle);
		free(r);
		return 1;
	}

	free(r);
	errno = ENOENT;
	return 0;
}