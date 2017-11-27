STRUCT_COUNTERS *
TC_READ_COUNTER(const IPT_CHAINLABEL chain,
		unsigned int rulenum,
		TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;

	iptc_fn = TC_READ_COUNTER;
	CHECK(*handle);

	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return NULL;
	}

	if (!(r = iptcc_get_rule_num(c, rulenum))) {
		errno = E2BIG;
		return NULL;
	}

	return &r->entry[0].counters;
}