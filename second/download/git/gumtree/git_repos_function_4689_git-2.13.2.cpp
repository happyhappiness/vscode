int xdl_emit_diff(xdfenv_t *xe, xdchange_t *xscr, xdemitcb_t *ecb,
		  xdemitconf_t const *xecfg) {
	long s1, s2, e1, e2, lctx;
	xdchange_t *xch, *xche;
	long funclineprev = -1;
	struct func_line func_line = { 0 };

	for (xch = xscr; xch; xch = xche->next) {
		xche = xdl_get_hunk(&xch, xecfg);
		if (!xch)
			break;

		s1 = XDL_MAX(xch->i1 - xecfg->ctxlen, 0);
		s2 = XDL_MAX(xch->i2 - xecfg->ctxlen, 0);

		if (xecfg->flags & XDL_EMIT_FUNCCONTEXT) {
			long fs1, i1 = xch->i1;

			/* Appended chunk? */
			if (i1 >= xe->xdf1.nrec) {
				char dummy[1];
				long i2 = xch->i2;

				/*
				 * We don't need additional context if
				 * a whole function was added.
				 */
				while (i2 < xe->xdf2.nrec) {
					if (match_func_rec(&xe->xdf2, xecfg, i2,
						dummy, sizeof(dummy)) >= 0)
						goto post_context_calculation;
					i2++;
				}

				/*
				 * Otherwise get more context from the
				 * pre-image.
				 */
				i1 = xe->xdf1.nrec - 1;
			}

			fs1 = get_func_line(xe, xecfg, NULL, i1, -1);
			if (fs1 < 0)
				fs1 = 0;
			if (fs1 < s1) {
				s2 -= s1 - fs1;
				s1 = fs1;
			}
		}

 post_context_calculation:
		lctx = xecfg->ctxlen;
		lctx = XDL_MIN(lctx, xe->xdf1.nrec - (xche->i1 + xche->chg1));
		lctx = XDL_MIN(lctx, xe->xdf2.nrec - (xche->i2 + xche->chg2));

		e1 = xche->i1 + xche->chg1 + lctx;
		e2 = xche->i2 + xche->chg2 + lctx;

		if (xecfg->flags & XDL_EMIT_FUNCCONTEXT) {
			long fe1 = get_func_line(xe, xecfg, NULL,
						 xche->i1 + xche->chg1,
						 xe->xdf1.nrec);
			while (fe1 > 0 && is_empty_rec(&xe->xdf1, fe1 - 1))
				fe1--;
			if (fe1 < 0)
				fe1 = xe->xdf1.nrec;
			if (fe1 > e1) {
				e2 += fe1 - e1;
				e1 = fe1;
			}

			/*
			 * Overlap with next change?  Then include it
			 * in the current hunk and start over to find
			 * its new end.
			 */
			if (xche->next) {
				long l = XDL_MIN(xche->next->i1,
						 xe->xdf1.nrec - 1);
				if (l - xecfg->ctxlen <= e1 ||
				    get_func_line(xe, xecfg, NULL, l, e1) < 0) {
					xche = xche->next;
					goto post_context_calculation;
				}
			}
		}

		/*
		 * Emit current hunk header.
		 */

		if (xecfg->flags & XDL_EMIT_FUNCNAMES) {
			get_func_line(xe, xecfg, &func_line,
				      s1 - 1, funclineprev);
			funclineprev = s1 - 1;
		}
		if (xdl_emit_hunk_hdr(s1 + 1, e1 - s1, s2 + 1, e2 - s2,
				      func_line.buf, func_line.len, ecb) < 0)
			return -1;

		/*
		 * Emit pre-context.
		 */
		for (; s2 < xch->i2; s2++)
			if (xdl_emit_record(&xe->xdf2, s2, " ", ecb) < 0)
				return -1;

		for (s1 = xch->i1, s2 = xch->i2;; xch = xch->next) {
			/*
			 * Merge previous with current change atom.
			 */
			for (; s1 < xch->i1 && s2 < xch->i2; s1++, s2++)
				if (xdl_emit_record(&xe->xdf2, s2, " ", ecb) < 0)
					return -1;

			/*
			 * Removes lines from the first file.
			 */
			for (s1 = xch->i1; s1 < xch->i1 + xch->chg1; s1++)
				if (xdl_emit_record(&xe->xdf1, s1, "-", ecb) < 0)
					return -1;

			/*
			 * Adds lines from the second file.
			 */
			for (s2 = xch->i2; s2 < xch->i2 + xch->chg2; s2++)
				if (xdl_emit_record(&xe->xdf2, s2, "+", ecb) < 0)
					return -1;

			if (xch == xche)
				break;
			s1 = xch->i1 + xch->chg1;
			s2 = xch->i2 + xch->chg2;
		}

		/*
		 * Emit post-context.
		 */
		for (s2 = xche->i2 + xche->chg2; s2 < e2; s2++)
			if (xdl_emit_record(&xe->xdf2, s2, " ", ecb) < 0)
				return -1;
	}

	return 0;
}