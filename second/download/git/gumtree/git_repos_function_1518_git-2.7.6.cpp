int xdi_diff(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp, xdemitconf_t const *xecfg, xdemitcb_t *xecb)
{
	mmfile_t a = *mf1;
	mmfile_t b = *mf2;

	if (mf1->size > MAX_XDIFF_SIZE || mf2->size > MAX_XDIFF_SIZE)
		return -1;

	trim_common_tail(&a, &b, xecfg->ctxlen);

	return xdl_diff(&a, &b, xpp, xecfg, xecb);
}