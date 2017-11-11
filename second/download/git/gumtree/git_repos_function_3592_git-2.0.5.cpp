static int xdl_merge_cmp_lines(xdfenv_t *xe1, int i1, xdfenv_t *xe2, int i2,
		int line_count, long flags)
{
	int i;
	xrecord_t **rec1 = xe1->xdf2.recs + i1;
	xrecord_t **rec2 = xe2->xdf2.recs + i2;

	for (i = 0; i < line_count; i++) {
		int result = xdl_recmatch(rec1[i]->ptr, rec1[i]->size,
			rec2[i]->ptr, rec2[i]->size, flags);
		if (!result)
			return -1;
	}
	return 0;
}