int
TC_REPLACE_ENTRY(const IPT_CHAINLABEL chain,
		 const STRUCT_ENTRY *e,
		 unsigned int rulenum,
		 TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r, *old;

	iptc_fn = TC_REPLACE_ENTRY;

	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	if (rulenum >= c->num_rules) {
		errno = E2BIG;
		return 0;
	}

	/* Take advantage of the double linked list if possible. */
	if (rulenum + 1 <= c->num_rules/2) {
		old = iptcc_get_rule_num(c, rulenum + 1);
	} else {
		old = iptcc_get_rule_num_reverse(c, c->num_rules - rulenum);
	}

	if (!(r = iptcc_alloc_rule(c, e->next_offset))) {
		errno = ENOMEM;
		return 0;
	}

	memcpy(r->entry, e, e->next_offset);
	r->counter_map.maptype = COUNTER_MAP_SET;

	if (!iptcc_map_target(*handle, r)) {
		free(r);
		return 0;
	}

	list_add(&r->list, &old->list);
	iptcc_delete_rule(old);

	set_changed(*handle);

	return 1;
}