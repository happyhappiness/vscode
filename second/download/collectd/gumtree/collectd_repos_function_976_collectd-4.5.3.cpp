static struct rule_head *iptcc_get_rule_num(struct chain_head *c,
					    unsigned int rulenum)
{
	struct rule_head *r;
	unsigned int num = 0;

	list_for_each_entry(r, &c->rules, list) {
		num++;
		if (num == rulenum)
			return r;
	}
	return NULL;
}