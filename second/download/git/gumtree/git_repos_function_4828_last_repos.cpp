static long match_func_rec(xdfile_t *xdf, xdemitconf_t const *xecfg, long ri,
			   char *buf, long sz)
{
	const char *rec;
	long len = xdl_get_rec(xdf, ri, &rec);
	if (!xecfg->find_func)
		return def_ff(rec, len, buf, sz, xecfg->find_func_priv);
	return xecfg->find_func(rec, len, buf, sz, xecfg->find_func_priv);
}