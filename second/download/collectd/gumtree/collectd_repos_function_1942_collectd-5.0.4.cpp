int
TC_ZERO_COUNTER(const IPT_CHAINLABEL chain,
		unsigned int rulenum,
		TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;
	
	iptc_fn = TC_ZERO_COUNTER;
	CHECK(*handle);

	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	if (!(r = iptcc_get_rule_num(c, rulenum))) {
		errno = E2BIG;
		return 0;
	}

	if (r->counter_map.maptype == COUNTER_MAP_NORMAL_MAP)
		r->counter_map.maptype = COUNTER_MAP_ZEROED;

	set_changed(*handle);

	return 1;
}