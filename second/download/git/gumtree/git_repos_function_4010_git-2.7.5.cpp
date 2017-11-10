static void xdl_mark_ignorable(xdchange_t *xscr, xdfenv_t *xe, long flags)
{
	xdchange_t *xch;

	for (xch = xscr; xch; xch = xch->next) {
		int ignore = 1;
		xrecord_t **rec;
		long i;

		rec = &xe->xdf1.recs[xch->i1];
		for (i = 0; i < xch->chg1 && ignore; i++)
			ignore = xdl_blankline(rec[i]->ptr, rec[i]->size, flags);

		rec = &xe->xdf2.recs[xch->i2];
		for (i = 0; i < xch->chg2 && ignore; i++)
			ignore = xdl_blankline(rec[i]->ptr, rec[i]->size, flags);

		xch->ignore = ignore;
	}
}