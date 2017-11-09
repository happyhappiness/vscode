static int try_lcs(struct histindex *index, struct region *lcs, int b_ptr,
	int line1, int count1, int line2, int count2)
{
	unsigned int b_next = b_ptr + 1;
	struct record *rec = index->records[TABLE_HASH(index, 2, b_ptr)];
	unsigned int as, ae, bs, be, np, rc;
	int should_break;

	for (; rec; rec = rec->next) {
		if (rec->cnt > index->cnt) {
			if (!index->has_common)
				index->has_common = CMP(index, 1, rec->ptr, 2, b_ptr);
			continue;
		}

		as = rec->ptr;
		if (!CMP(index, 1, as, 2, b_ptr))
			continue;

		index->has_common = 1;
		for (;;) {
			should_break = 0;
			np = NEXT_PTR(index, as);
			bs = b_ptr;
			ae = as;
			be = bs;
			rc = rec->cnt;

			while (line1 < as && line2 < bs
				&& CMP(index, 1, as - 1, 2, bs - 1)) {
				as--;
				bs--;
				if (1 < rc)
					rc = XDL_MIN(rc, CNT(index, as));
			}
			while (ae < LINE_END(1) && be < LINE_END(2)
				&& CMP(index, 1, ae + 1, 2, be + 1)) {
				ae++;
				be++;
				if (1 < rc)
					rc = XDL_MIN(rc, CNT(index, ae));
			}

			if (b_next <= be)
				b_next = be + 1;
			if (lcs->end1 - lcs->begin1 < ae - as || rc < index->cnt) {
				lcs->begin1 = as;
				lcs->begin2 = bs;
				lcs->end1 = ae;
				lcs->end2 = be;
				index->cnt = rc;
			}

			if (np == 0)
				break;

			while (np <= ae) {
				np = NEXT_PTR(index, np);
				if (np == 0) {
					should_break = 1;
					break;
				}
			}

			if (should_break)
				break;

			as = np;
		}
	}
	return b_next;
}