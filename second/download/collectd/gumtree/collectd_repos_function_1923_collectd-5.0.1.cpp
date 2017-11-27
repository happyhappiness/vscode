int
TC_INSERT_ENTRY(const IPT_CHAINLABEL chain,
		const STRUCT_ENTRY *e,
		unsigned int rulenum,
		TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;
	struct list_head *prev;

	iptc_fn = TC_INSERT_ENTRY;

	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	/* first rulenum index = 0
	   first c->num_rules index = 1 */
	if (rulenum > c->num_rules) {
		errno = E2BIG;
		return 0;
	}

	/* If we are inserting at the end just take advantage of the
	   double linked list, insert will happen before the entry
	   prev points to. */
	if (rulenum == c->num_rules) {
		prev = &c->rules;
	} else if (rulenum + 1 <= c->num_rules/2) {
		r = iptcc_get_rule_num(c, rulenum + 1);
		prev = &r->list;
	} else {
		r = iptcc_get_rule_num_reverse(c, c->num_rules - rulenum);
		prev = &r->list;
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

	list_add_tail(&r->list, prev);
	c->num_rules++;

	set_changed(*handle);

	return 1;
}