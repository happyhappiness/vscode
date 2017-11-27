int
TC_DELETE_NUM_ENTRY(const IPT_CHAINLABEL chain,
		    unsigned int rulenum,
		    TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;

	iptc_fn = TC_DELETE_NUM_ENTRY;

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
		r = iptcc_get_rule_num(c, rulenum + 1);
	} else {
		r = iptcc_get_rule_num_reverse(c, c->num_rules - rulenum);
	}

	/* If we are about to delete the rule that is the current
	 * iterator, move rule iterator back.  next pointer will then
	 * point to real next node */
	if (r == (*handle)->rule_iterator_cur) {
		(*handle)->rule_iterator_cur = 
			list_entry((*handle)->rule_iterator_cur->list.prev,
				   struct rule_head, list);
	}

	c->num_rules--;
	iptcc_delete_rule(r);

	set_changed(*handle);

	return 1;
}