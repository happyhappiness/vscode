int
TC_FLUSH_ENTRIES(const IPT_CHAINLABEL chain, TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r, *tmp;

	iptc_fn = TC_FLUSH_ENTRIES;
	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	list_for_each_entry_safe(r, tmp, &c->rules, list) {
		iptcc_delete_rule(r);
	}

	c->num_rules = 0;

	set_changed(*handle);

	return 1;
}