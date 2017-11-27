static int cache_add_entry(STRUCT_ENTRY *e, 
			   TC_HANDLE_T h, 
			   STRUCT_ENTRY **prev,
			   unsigned int *num)
{
	unsigned int builtin;
	unsigned int offset = (char *)e - (char *)h->entries->entrytable;

	DEBUGP("entering...");

	/* Last entry ("policy rule"). End it.*/
	if (iptcb_entry2offset(h,e) + e->next_offset == h->entries->size) {
		/* This is the ERROR node at the end of the chain */
		DEBUGP_C("%u:%u: end of table:\n", *num, offset);

		__iptcc_p_del_policy(h, *num);

		h->chain_iterator_cur = NULL;
		goto out_inc;
	}

	/* We know this is the start of a new chain if it's an ERROR
	 * target, or a hook entry point */

	if (strcmp(GET_TARGET(e)->u.user.name, ERROR_TARGET) == 0) {
		struct chain_head *c = 
			iptcc_alloc_chain_head((const char *)GET_TARGET(e)->data, 0);
		DEBUGP_C("%u:%u:new userdefined chain %s: %p\n", *num, offset, 
			(char *)c->name, c);
		if (!c) {
			errno = -ENOMEM;
			return -1;
		}
		h->num_chains++; /* New user defined chain */

		__iptcc_p_add_chain(h, c, offset, num);

	} else if ((builtin = iptcb_ent_is_hook_entry(e, h)) != 0) {
		struct chain_head *c =
			iptcc_alloc_chain_head((char *)hooknames[builtin-1], 
						builtin);
		DEBUGP_C("%u:%u new builtin chain: %p (rules=%p)\n", 
			*num, offset, c, &c->rules);
		if (!c) {
			errno = -ENOMEM;
			return -1;
		}

		c->hooknum = builtin;

		__iptcc_p_add_chain(h, c, offset, num);

		/* FIXME: this is ugly. */
		goto new_rule;
	} else {
		/* has to be normal rule */
		struct rule_head *r;
new_rule:

		if (!(r = iptcc_alloc_rule(h->chain_iterator_cur, 
					   e->next_offset))) {
			errno = ENOMEM;
			return -1;
		}
		DEBUGP_C("%u:%u normal rule: %p: ", *num, offset, r);

		r->index = *num;
		r->offset = offset;
		memcpy(r->entry, e, e->next_offset);
		r->counter_map.maptype = COUNTER_MAP_NORMAL_MAP;
		r->counter_map.mappos = r->index;

		/* handling of jumps, etc. */
		if (!strcmp(GET_TARGET(e)->u.user.name, STANDARD_TARGET)) {
			STRUCT_STANDARD_TARGET *t;

			t = (STRUCT_STANDARD_TARGET *)GET_TARGET(e);
			if (t->target.u.target_size
			    != ALIGN(sizeof(STRUCT_STANDARD_TARGET))) {
				errno = EINVAL;
				return -1;
			}

			if (t->verdict < 0) {
				DEBUGP_C("standard, verdict=%d\n", t->verdict);
				r->type = IPTCC_R_STANDARD;
			} else if (t->verdict == r->offset+e->next_offset) {
				DEBUGP_C("fallthrough\n");
				r->type = IPTCC_R_FALLTHROUGH;
			} else {
				DEBUGP_C("jump, target=%u\n", t->verdict);
				r->type = IPTCC_R_JUMP;
				/* Jump target fixup has to be deferred
				 * until second pass, since we migh not
				 * yet have parsed the target */
			}
		} else {
			DEBUGP_C("module, target=%s\n", GET_TARGET(e)->u.user.name);
			r->type = IPTCC_R_MODULE;
		}

		list_add_tail(&r->list, &h->chain_iterator_cur->rules);
		h->chain_iterator_cur->num_rules++;
	}
out_inc:
	(*num)++;
	return 0;
}