int 
TC_SET_COUNTER(const IPT_CHAINLABEL chain,
	       unsigned int rulenum,
	       STRUCT_COUNTERS *counters,
	       TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;
	STRUCT_ENTRY *e;

	iptc_fn = TC_SET_COUNTER;
	CHECK(*handle);

	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	if (!(r = iptcc_get_rule_num(c, rulenum))) {
		errno = E2BIG;
		return 0;
	}

	e = r->entry;
	r->counter_map.maptype = COUNTER_MAP_SET;

	memcpy(&e->counters, counters, sizeof(STRUCT_COUNTERS));

	set_changed(*handle);

	return 1;
}