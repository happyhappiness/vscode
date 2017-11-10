static int xdl_do_merge(xdfenv_t *xe1, xdchange_t *xscr1,
		xdfenv_t *xe2, xdchange_t *xscr2,
		xmparam_t const *xmp, mmbuffer_t *result)
{
	xdmerge_t *changes, *c;
	xpparam_t const *xpp = &xmp->xpp;
	const char *const ancestor_name = xmp->ancestor;
	const char *const name1 = xmp->file1;
	const char *const name2 = xmp->file2;
	int i0, i1, i2, chg0, chg1, chg2;
	int level = xmp->level;
	int style = xmp->style;
	int favor = xmp->favor;

	if (style == XDL_MERGE_DIFF3) {
		/*
		 * "diff3 -m" output does not make sense for anything
		 * more aggressive than XDL_MERGE_EAGER.
		 */
		if (XDL_MERGE_EAGER < level)
			level = XDL_MERGE_EAGER;
	}

	c = changes = NULL;

	while (xscr1 && xscr2) {
		if (!changes)
			changes = c;
		if (xscr1->i1 + xscr1->chg1 < xscr2->i1) {
			i0 = xscr1->i1;
			i1 = xscr1->i2;
			i2 = xscr2->i2 - xscr2->i1 + xscr1->i1;
			chg0 = xscr1->chg1;
			chg1 = xscr1->chg2;
			chg2 = xscr1->chg1;
			if (xdl_append_merge(&c, 1,
					     i0, chg0, i1, chg1, i2, chg2)) {
				xdl_cleanup_merge(changes);
				return -1;
			}
			xscr1 = xscr1->next;
			continue;
		}
		if (xscr2->i1 + xscr2->chg1 < xscr1->i1) {
			i0 = xscr2->i1;
			i1 = xscr1->i2 - xscr1->i1 + xscr2->i1;
			i2 = xscr2->i2;
			chg0 = xscr2->chg1;
			chg1 = xscr2->chg1;
			chg2 = xscr2->chg2;
			if (xdl_append_merge(&c, 2,
					     i0, chg0, i1, chg1, i2, chg2)) {
				xdl_cleanup_merge(changes);
				return -1;
			}
			xscr2 = xscr2->next;
			continue;
		}
		if (level == XDL_MERGE_MINIMAL || xscr1->i1 != xscr2->i1 ||
				xscr1->chg1 != xscr2->chg1 ||
				xscr1->chg2 != xscr2->chg2 ||
				xdl_merge_cmp_lines(xe1, xscr1->i2,
					xe2, xscr2->i2,
					xscr1->chg2, xpp->flags)) {
			/* conflict */
			int off = xscr1->i1 - xscr2->i1;
			int ffo = off + xscr1->chg1 - xscr2->chg1;

			i0 = xscr1->i1;
			i1 = xscr1->i2;
			i2 = xscr2->i2;
			if (off > 0) {
				i0 -= off;
				i1 -= off;
			}
			else
				i2 += off;
			chg0 = xscr1->i1 + xscr1->chg1 - i0;
			chg1 = xscr1->i2 + xscr1->chg2 - i1;
			chg2 = xscr2->i2 + xscr2->chg2 - i2;
			if (ffo < 0) {
				chg0 -= ffo;
				chg1 -= ffo;
			} else
				chg2 += ffo;
			if (xdl_append_merge(&c, 0,
					     i0, chg0, i1, chg1, i2, chg2)) {
				xdl_cleanup_merge(changes);
				return -1;
			}
		}

		i1 = xscr1->i1 + xscr1->chg1;
		i2 = xscr2->i1 + xscr2->chg1;

		if (i1 >= i2)
			xscr2 = xscr2->next;
		if (i2 >= i1)
			xscr1 = xscr1->next;
	}
	while (xscr1) {
		if (!changes)
			changes = c;
		i0 = xscr1->i1;
		i1 = xscr1->i2;
		i2 = xscr1->i1 + xe2->xdf2.nrec - xe2->xdf1.nrec;
		chg0 = xscr1->chg1;
		chg1 = xscr1->chg2;
		chg2 = xscr1->chg1;
		if (xdl_append_merge(&c, 1,
				     i0, chg0, i1, chg1, i2, chg2)) {
			xdl_cleanup_merge(changes);
			return -1;
		}
		xscr1 = xscr1->next;
	}
	while (xscr2) {
		if (!changes)
			changes = c;
		i0 = xscr2->i1;
		i1 = xscr2->i1 + xe1->xdf2.nrec - xe1->xdf1.nrec;
		i2 = xscr2->i2;
		chg0 = xscr2->chg1;
		chg1 = xscr2->chg1;
		chg2 = xscr2->chg2;
		if (xdl_append_merge(&c, 2,
				     i0, chg0, i1, chg1, i2, chg2)) {
			xdl_cleanup_merge(changes);
			return -1;
		}
		xscr2 = xscr2->next;
	}
	if (!changes)
		changes = c;
	/* refine conflicts */
	if (XDL_MERGE_ZEALOUS <= level &&
	    (xdl_refine_conflicts(xe1, xe2, changes, xpp) < 0 ||
	     xdl_simplify_non_conflicts(xe1, changes,
					XDL_MERGE_ZEALOUS < level) < 0)) {
		xdl_cleanup_merge(changes);
		return -1;
	}
	/* output */
	if (result) {
		int marker_size = xmp->marker_size;
		int size = xdl_fill_merge_buffer(xe1, name1, xe2, name2,
						 ancestor_name,
						 favor, changes, NULL, style,
						 marker_size);
		result->ptr = xdl_malloc(size);
		if (!result->ptr) {
			xdl_cleanup_merge(changes);
			return -1;
		}
		result->size = size;
		xdl_fill_merge_buffer(xe1, name1, xe2, name2,
				      ancestor_name, favor, changes,
				      result->ptr, style, marker_size);
	}
	return xdl_cleanup_merge(changes);
}