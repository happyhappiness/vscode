static int xdl_refine_conflicts(xdfenv_t *xe1, xdfenv_t *xe2, xdmerge_t *m,
		xpparam_t const *xpp)
{
	for (; m; m = m->next) {
		mmfile_t t1, t2;
		xdfenv_t xe;
		xdchange_t *xscr, *x;
		int i1 = m->i1, i2 = m->i2;

		/* let's handle just the conflicts */
		if (m->mode)
			continue;

		/* no sense refining a conflict when one side is empty */
		if (m->chg1 == 0 || m->chg2 == 0)
			continue;

		/*
		 * This probably does not work outside git, since
		 * we have a very simple mmfile structure.
		 */
		t1.ptr = (char *)xe1->xdf2.recs[m->i1]->ptr;
		t1.size = xe1->xdf2.recs[m->i1 + m->chg1 - 1]->ptr
			+ xe1->xdf2.recs[m->i1 + m->chg1 - 1]->size - t1.ptr;
		t2.ptr = (char *)xe2->xdf2.recs[m->i2]->ptr;
		t2.size = xe2->xdf2.recs[m->i2 + m->chg2 - 1]->ptr
			+ xe2->xdf2.recs[m->i2 + m->chg2 - 1]->size - t2.ptr;
		if (xdl_do_diff(&t1, &t2, xpp, &xe) < 0)
			return -1;
		if (xdl_change_compact(&xe.xdf1, &xe.xdf2, xpp->flags) < 0 ||
		    xdl_change_compact(&xe.xdf2, &xe.xdf1, xpp->flags) < 0 ||
		    xdl_build_script(&xe, &xscr) < 0) {
			xdl_free_env(&xe);
			return -1;
		}
		if (!xscr) {
			/* If this happens, the changes are identical. */
			xdl_free_env(&xe);
			m->mode = 4;
			continue;
		}
		x = xscr;
		m->i1 = xscr->i1 + i1;
		m->chg1 = xscr->chg1;
		m->i2 = xscr->i2 + i2;
		m->chg2 = xscr->chg2;
		while (xscr->next) {
			xdmerge_t *m2 = xdl_malloc(sizeof(xdmerge_t));
			if (!m2) {
				xdl_free_env(&xe);
				xdl_free_script(x);
				return -1;
			}
			xscr = xscr->next;
			m2->next = m->next;
			m->next = m2;
			m = m2;
			m->mode = 0;
			m->i1 = xscr->i1 + i1;
			m->chg1 = xscr->chg1;
			m->i2 = xscr->i2 + i2;
			m->chg2 = xscr->chg2;
		}
		xdl_free_env(&xe);
		xdl_free_script(x);
	}
	return 0;
}