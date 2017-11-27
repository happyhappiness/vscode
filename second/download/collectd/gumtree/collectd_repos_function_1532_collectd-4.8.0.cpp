static inline int iptcc_compile_rule (TC_HANDLE_T h, STRUCT_REPLACE *repl, struct rule_head *r)
{
	/* handle jumps */
	if (r->type == IPTCC_R_JUMP) {
		STRUCT_STANDARD_TARGET *t;
		t = (STRUCT_STANDARD_TARGET *)GET_TARGET(r->entry);
		/* memset for memcmp convenience on delete/replace */
		memset(t->target.u.user.name, 0, FUNCTION_MAXNAMELEN);
		strcpy(t->target.u.user.name, STANDARD_TARGET);
		/* Jumps can only happen to builtin chains, so we
		 * can safely assume that they always have a header */
		t->verdict = r->jump->head_offset + IPTCB_CHAIN_START_SIZE;
	} else if (r->type == IPTCC_R_FALLTHROUGH) {
		STRUCT_STANDARD_TARGET *t;
		t = (STRUCT_STANDARD_TARGET *)GET_TARGET(r->entry);
		t->verdict = r->offset + r->size;
	}
	
	/* copy entry from cache to blob */
	memcpy((char *)repl->entries+r->offset, r->entry, r->size);

	return 1;
}