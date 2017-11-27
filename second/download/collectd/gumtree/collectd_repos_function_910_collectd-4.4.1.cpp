const STRUCT_ENTRY *TC_GET_RULE(const char *chain,
				unsigned int n,
				TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;
	
	iptc_fn = TC_GET_RULE;

	CHECK(*handle);

	c = iptcc_find_label(chain, *handle);
	if (!c) {
		errno = ENOENT;
		return NULL;
	}

	r = iptcc_get_rule_num(c, n);
	if (!r)
		return NULL;
	return r->entry;
}