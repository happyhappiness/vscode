static int iptcc_compile_chain(TC_HANDLE_T h, STRUCT_REPLACE *repl, struct chain_head *c)
{
	int ret;
	struct rule_head *r;
	struct iptcb_chain_start *head;
	struct iptcb_chain_foot *foot;

	/* only user-defined chains have heaer */
	if (!iptcc_is_builtin(c)) {
		/* put chain header in place */
		head = (void *)repl->entries + c->head_offset;
		head->e.target_offset = sizeof(STRUCT_ENTRY);
		head->e.next_offset = IPTCB_CHAIN_START_SIZE;
		strcpy(head->name.t.u.user.name, ERROR_TARGET);
		head->name.t.u.target_size = 
				ALIGN(sizeof(struct ipt_error_target));
		strcpy(head->name.error, c->name);
	} else {
		repl->hook_entry[c->hooknum-1] = c->head_offset;	
		repl->underflow[c->hooknum-1] = c->foot_offset;
	}

	/* iterate over rules */
	list_for_each_entry(r, &c->rules, list) {
		ret = iptcc_compile_rule(h, repl, r);
		if (ret < 0)
			return ret;
	}

	/* put chain footer in place */
	foot = (void *)repl->entries + c->foot_offset;
	foot->e.target_offset = sizeof(STRUCT_ENTRY);
	foot->e.next_offset = IPTCB_CHAIN_FOOT_SIZE;
	strcpy(foot->target.target.u.user.name, STANDARD_TARGET);
	foot->target.target.u.target_size =
				ALIGN(sizeof(STRUCT_STANDARD_TARGET));
	/* builtin targets have verdict, others return */
	if (iptcc_is_builtin(c))
		foot->target.verdict = c->verdict;
	else
		foot->target.verdict = RETURN;
	/* set policy-counters */
	memcpy(&foot->e.counters, &c->counters, sizeof(STRUCT_COUNTERS));

	return 0;
}