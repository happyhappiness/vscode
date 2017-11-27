const STRUCT_ENTRY *
TC_FIRST_RULE(const char *chain, TC_HANDLE_T *handle)
{
	struct chain_head *c;
	struct rule_head *r;

	iptc_fn = TC_FIRST_RULE;

	DEBUGP("first rule(%s): ", chain);

	c = iptcc_find_label(chain, *handle);
	if (!c) {
		errno = ENOENT;
		return NULL;
	}

	/* Empty chain: single return/policy rule */
	if (list_empty(&c->rules)) {
		DEBUGP_C("no rules, returning NULL\n");
		return NULL;
	}

	r = list_entry(c->rules.next, struct rule_head, list);
	(*handle)->rule_iterator_cur = r;
	DEBUGP_C("%p\n", r);

	return r->entry;
}