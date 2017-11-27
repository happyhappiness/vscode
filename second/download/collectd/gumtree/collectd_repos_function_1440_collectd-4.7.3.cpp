int
TC_ZERO_ENTRIES(const IPT_CHAINLABEL chain, TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;

	iptc_fn = TC_ZERO_ENTRIES;
	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	if (c->counter_map.maptype == COUNTER_MAP_NORMAL_MAP)
		c->counter_map.maptype = COUNTER_MAP_ZEROED;

	list_for_each_entry(r, &c->rules, list) {
		if (r->counter_map.maptype == COUNTER_MAP_NORMAL_MAP)
			r->counter_map.maptype = COUNTER_MAP_ZEROED;
	}

	set_changed(*handle);

	return 1;
}