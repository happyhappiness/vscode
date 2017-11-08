static long get_func_line(xdfenv_t *xe, xdemitconf_t const *xecfg,
			  struct func_line *func_line, long start, long limit)
{
	find_func_t ff = xecfg->find_func ? xecfg->find_func : def_ff;
	long l, size, step = (start > limit) ? -1 : 1;
	char *buf, dummy[1];

	buf = func_line ? func_line->buf : dummy;
	size = func_line ? sizeof(func_line->buf) : sizeof(dummy);

	for (l = start; l != limit && 0 <= l && l < xe->xdf1.nrec; l += step) {
		const char *rec;
		long reclen = xdl_get_rec(&xe->xdf1, l, &rec);
		long len = ff(rec, reclen, buf, size, xecfg->find_func_priv);
		if (len >= 0) {
			if (func_line)
				func_line->len = len;
			return l;
		}
	}
	return -1;
}