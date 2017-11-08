static int xdl_emit_common(xdfenv_t *xe, xdchange_t *xscr, xdemitcb_t *ecb,
                           xdemitconf_t const *xecfg) {
	xdfile_t *xdf = &xe->xdf2;
	const char *rchg = xdf->rchg;
	long ix;

	for (ix = 0; ix < xdf->nrec; ix++) {
		if (rchg[ix])
			continue;
		if (xdl_emit_record(xdf, ix, "", ecb))
			return -1;
	}
	return 0;
}