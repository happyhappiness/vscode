int xdl_diff(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp,
	     xdemitconf_t const *xecfg, xdemitcb_t *ecb) {
	xdchange_t *xscr;
	xdfenv_t xe;
	emit_func_t ef = xecfg->hunk_func ? xdl_call_hunk_func : xdl_emit_diff;

	if (xdl_do_diff(mf1, mf2, xpp, &xe) < 0) {

		return -1;
	}
	if (xdl_change_compact(&xe.xdf1, &xe.xdf2, xpp->flags) < 0 ||
	    xdl_change_compact(&xe.xdf2, &xe.xdf1, xpp->flags) < 0 ||
	    xdl_build_script(&xe, &xscr) < 0) {

		xdl_free_env(&xe);
		return -1;
	}
	if (xscr) {
		if (xpp->flags & XDF_IGNORE_BLANK_LINES)
			xdl_mark_ignorable(xscr, &xe, xpp->flags);

		if (ef(&xe, xscr, ecb, xecfg) < 0) {

			xdl_free_script(xscr);
			xdl_free_env(&xe);
			return -1;
		}
		xdl_free_script(xscr);
	}
	xdl_free_env(&xe);

	return 0;
}