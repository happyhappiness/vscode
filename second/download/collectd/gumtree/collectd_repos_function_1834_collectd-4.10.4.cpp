static int parse_table(TC_HANDLE_T h)
{
	STRUCT_ENTRY *prev;
	unsigned int num = 0;
	struct chain_head *c;

	/* First pass: over ruleset blob */
	ENTRY_ITERATE(h->entries->entrytable, h->entries->size,
			cache_add_entry, h, &prev, &num);

	/* Build the chain index, used for chain list search speedup */
	if ((iptcc_chain_index_alloc(h)) < 0)
		return -ENOMEM;
	iptcc_chain_index_build(h);

	/* Second pass: fixup parsed data from first pass */
	list_for_each_entry(c, &h->chains, list) {
		struct rule_head *r;
		list_for_each_entry(r, &c->rules, list) {
			struct chain_head *lc;
			STRUCT_STANDARD_TARGET *t;

			if (r->type != IPTCC_R_JUMP)
				continue;

			t = (STRUCT_STANDARD_TARGET *)GET_TARGET(r->entry);
			lc = iptcc_find_chain_by_offset(h, t->verdict);
			if (!lc)
				return -1;
			r->jump = lc;
			lc->references++;
		}
	}

	/* FIXME: sort chains */

	return 1;
}