static int scanA(struct histindex *index, int line1, int count1)
{
	unsigned int ptr, tbl_idx;
	unsigned int chain_len;
	struct record **rec_chain, *rec;

	for (ptr = LINE_END(1); line1 <= ptr; ptr--) {
		tbl_idx = TABLE_HASH(index, 1, ptr);
		rec_chain = index->records + tbl_idx;
		rec = *rec_chain;

		chain_len = 0;
		while (rec) {
			if (CMP(index, 1, rec->ptr, 1, ptr)) {
				/*
				 * ptr is identical to another element. Insert
				 * it onto the front of the existing element
				 * chain.
				 */
				NEXT_PTR(index, ptr) = rec->ptr;
				rec->ptr = ptr;
				/* cap rec->cnt at MAX_CNT */
				rec->cnt = XDL_MIN(MAX_CNT, rec->cnt + 1);
				LINE_MAP(index, ptr) = rec;
				goto continue_scan;
			}

			rec = rec->next;
			chain_len++;
		}

		if (chain_len == index->max_chain_length)
			return -1;

		/*
		 * This is the first time we have ever seen this particular
		 * element in the sequence. Construct a new chain for it.
		 */
		if (!(rec = xdl_cha_alloc(&index->rcha)))
			return -1;
		rec->ptr = ptr;
		rec->cnt = 1;
		rec->next = *rec_chain;
		*rec_chain = rec;
		LINE_MAP(index, ptr) = rec;

continue_scan:
		; /* no op */
	}

	return 0;
}