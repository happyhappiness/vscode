static int histogram_diff(xpparam_t const *xpp, xdfenv_t *env,
	int line1, int count1, int line2, int count2)
{
	struct histindex index;
	struct region lcs;
	int sz;
	int result = -1;

	if (count1 <= 0 && count2 <= 0)
		return 0;

	if (LINE_END(1) >= MAX_PTR)
		return -1;

	if (!count1) {
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		return 0;
	} else if (!count2) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		return 0;
	}

	memset(&index, 0, sizeof(index));

	index.env = env;
	index.xpp = xpp;

	index.records = NULL;
	index.line_map = NULL;
	/* in case of early xdl_cha_free() */
	index.rcha.head = NULL;

	index.table_bits = xdl_hashbits(count1);
	sz = index.records_size = 1 << index.table_bits;
	sz *= sizeof(struct record *);
	if (!(index.records = (struct record **) xdl_malloc(sz)))
		goto cleanup;
	memset(index.records, 0, sz);

	sz = index.line_map_size = count1;
	sz *= sizeof(struct record *);
	if (!(index.line_map = (struct record **) xdl_malloc(sz)))
		goto cleanup;
	memset(index.line_map, 0, sz);

	sz = index.line_map_size;
	sz *= sizeof(unsigned int);
	if (!(index.next_ptrs = (unsigned int *) xdl_malloc(sz)))
		goto cleanup;
	memset(index.next_ptrs, 0, sz);

	/* lines / 4 + 1 comes from xprepare.c:xdl_prepare_ctx() */
	if (xdl_cha_init(&index.rcha, sizeof(struct record), count1 / 4 + 1) < 0)
		goto cleanup;

	index.ptr_shift = line1;
	index.max_chain_length = 64;

	memset(&lcs, 0, sizeof(lcs));
	if (find_lcs(&index, &lcs, line1, count1, line2, count2))
		result = fall_back_to_classic_diff(&index, line1, count1, line2, count2);
	else {
		if (lcs.begin1 == 0 && lcs.begin2 == 0) {
			while (count1--)
				env->xdf1.rchg[line1++ - 1] = 1;
			while (count2--)
				env->xdf2.rchg[line2++ - 1] = 1;
			result = 0;
		} else {
			result = histogram_diff(xpp, env,
						line1, lcs.begin1 - line1,
						line2, lcs.begin2 - line2);
			if (result)
				goto cleanup;
			result = histogram_diff(xpp, env,
						lcs.end1 + 1, LINE_END(1) - lcs.end1,
						lcs.end2 + 1, LINE_END(2) - lcs.end2);
			if (result)
				goto cleanup;
		}
	}

cleanup:
	xdl_free(index.records);
	xdl_free(index.line_map);
	xdl_free(index.next_ptrs);
	xdl_cha_free(&index.rcha);

	return result;
}