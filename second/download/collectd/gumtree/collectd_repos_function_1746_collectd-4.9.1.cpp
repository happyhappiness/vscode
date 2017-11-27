static int iptcc_compile_chain_offsets(TC_HANDLE_T h, struct chain_head *c,
				       unsigned int *offset, unsigned int *num)
{
	struct rule_head *r;

	c->head_offset = *offset;
	DEBUGP("%s: chain_head %u, offset=%u\n", c->name, *num, *offset);

	if (!iptcc_is_builtin(c))  {
		/* Chain has header */
		*offset += sizeof(STRUCT_ENTRY) 
			     + ALIGN(sizeof(struct ipt_error_target));
		(*num)++;
	}

	list_for_each_entry(r, &c->rules, list) {
		DEBUGP("rule %u, offset=%u, index=%u\n", *num, *offset, *num);
		r->offset = *offset;
		r->index = *num;
		*offset += r->size;
		(*num)++;
	}

	DEBUGP("%s; chain_foot %u, offset=%u, index=%u\n", c->name, *num, 
		*offset, *num);
	c->foot_offset = *offset;
	c->foot_index = *num;
	*offset += sizeof(STRUCT_ENTRY)
		   + ALIGN(sizeof(STRUCT_STANDARD_TARGET));
	(*num)++;

	return 1;
}