static int iptcc_compile_table_prep(TC_HANDLE_T h, unsigned int *size)
{
	struct chain_head *c;
	unsigned int offset = 0, num = 0;
	int ret = 0;

	/* First pass: calculate offset for every rule */
	list_for_each_entry(c, &h->chains, list) {
		ret = iptcc_compile_chain_offsets(h, c, &offset, &num);
		if (ret < 0)
			return ret;
	}

	/* Append one error rule at end of chain */
	num++;
	offset += sizeof(STRUCT_ENTRY)
		  + ALIGN(sizeof(struct ipt_error_target));

	/* ruleset size is now in offset */
	*size = offset;
	return num;
}