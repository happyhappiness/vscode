static int xdl_emit_record(xdfile_t *xdf, long ri, char const *pre, xdemitcb_t *ecb) {
	long size, psize = strlen(pre);
	char const *rec;

	size = xdl_get_rec(xdf, ri, &rec);
	if (xdl_emit_diffrec(rec, size, pre, psize, ecb) < 0) {

		return -1;
	}

	return 0;
}