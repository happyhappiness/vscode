static int is_empty_rec(xdfile_t *xdf, long ri)
{
	const char *rec;
	long len = xdl_get_rec(xdf, ri, &rec);

	while (len > 0 && XDL_ISSPACE(*rec)) {
		rec++;
		len--;
	}
	return !len;
}