const STRUCT_ENTRY *
TC_NEXT_RULE(const STRUCT_ENTRY *prev, TC_HANDLE_T *handle)
{
	struct rule_head *r;

	iptc_fn = TC_NEXT_RULE;
	DEBUGP("rule_iterator_cur=%p...", (*handle)->rule_iterator_cur);

	if (!(*handle)->rule_iterator_cur) {
		DEBUGP_C("returning NULL\n");
		return NULL;
	}
	
	r = list_entry((*handle)->rule_iterator_cur->list.next, 
			struct rule_head, list);

	iptc_fn = TC_NEXT_RULE;

	DEBUGP_C("next=%p, head=%p...", &r->list, 
		&(*handle)->rule_iterator_cur->chain->rules);

	if (&r->list == &(*handle)->rule_iterator_cur->chain->rules) {
		(*handle)->rule_iterator_cur = NULL;
		DEBUGP_C("finished, returning NULL\n");
		return NULL;
	}

	(*handle)->rule_iterator_cur = r;

	/* NOTE: prev is without any influence ! */
	DEBUGP_C("returning rule %p\n", r);
	return r->entry;
}