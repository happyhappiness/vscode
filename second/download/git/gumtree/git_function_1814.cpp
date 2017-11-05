static void show_diff(struct merge_list *entry)
{
	unsigned long size;
	mmfile_t src, dst;
	xpparam_t xpp;
	xdemitconf_t xecfg;
	xdemitcb_t ecb;

	xpp.flags = 0;
	memset(&xecfg, 0, sizeof(xecfg));
	xecfg.ctxlen = 3;
	ecb.outf = show_outf;
	ecb.priv = NULL;

	src.ptr = origin(entry, &size);
	if (!src.ptr)
		size = 0;
	src.size = size;
	dst.ptr = result(entry, &size);
	if (!dst.ptr)
		size = 0;
	dst.size = size;
	if (xdi_diff(&src, &dst, &xpp, &xecfg, &ecb))
		die("unable to generate diff");
	free(src.ptr);
	free(dst.ptr);
}