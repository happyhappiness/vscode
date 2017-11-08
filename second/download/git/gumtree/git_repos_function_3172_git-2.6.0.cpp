static int generate_common_file(mmfile_t *res, mmfile_t *f1, mmfile_t *f2)
{
	unsigned long size = f1->size < f2->size ? f1->size : f2->size;
	void *ptr = xmalloc(size);
	xpparam_t xpp;
	xdemitconf_t xecfg;
	xdemitcb_t ecb;

	memset(&xpp, 0, sizeof(xpp));
	xpp.flags = 0;
	memset(&xecfg, 0, sizeof(xecfg));
	xecfg.ctxlen = 3;
	xecfg.flags = XDL_EMIT_COMMON;
	ecb.outf = common_outf;

	res->ptr = ptr;
	res->size = 0;

	ecb.priv = res;
	return xdi_diff(f1, f2, &xpp, &xecfg, &ecb);
}