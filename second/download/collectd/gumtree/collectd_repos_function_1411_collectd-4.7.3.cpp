static int iptcc_compile_table(TC_HANDLE_T h, STRUCT_REPLACE *repl)
{
	struct chain_head *c;
	struct iptcb_chain_error *error;

	/* Second pass: copy from cache to offsets, fill in jumps */
	list_for_each_entry(c, &h->chains, list) {
		int ret = iptcc_compile_chain(h, repl, c);
		if (ret < 0)
			return ret;
	}

	/* Append error rule at end of chain */
	error = (void *)repl->entries + repl->size - IPTCB_CHAIN_ERROR_SIZE;
	error->entry.target_offset = sizeof(STRUCT_ENTRY);
	error->entry.next_offset = IPTCB_CHAIN_ERROR_SIZE;
	error->target.t.u.user.target_size = 
		ALIGN(sizeof(struct ipt_error_target));
	strcpy((char *)&error->target.t.u.user.name, ERROR_TARGET);
	strcpy((char *)&error->target.error, "ERROR");

	return 1;
}