int
TC_APPEND_ENTRY(const IPT_CHAINLABEL chain,
		const STRUCT_ENTRY *e,
		TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;

	iptc_fn = TC_APPEND_ENTRY;
	if (!(c = iptcc_find_label(chain, *handle))) {
		DEBUGP("unable to find chain `%s'\n", chain);
		errno = ENOENT;
		return 0;
	}

	if (!(r = iptcc_alloc_rule(c, e->next_offset))) {
		DEBUGP("unable to allocate rule for chain `%s'\n", chain);
		errno = ENOMEM;
		return 0;
	}

	memcpy(r->entry, e, e->next_offset);
	r->counter_map.maptype = COUNTER_MAP_SET;

	if (!iptcc_map_target(*handle, r)) {
		DEBUGP("unable to map target of rule for chain `%s'\n", chain);
		free(r);
		return 0;
	}

	list_add_tail(&r->list, &c->rules);
	c->num_rules++;

	set_changed(*handle);

	return 1;
}