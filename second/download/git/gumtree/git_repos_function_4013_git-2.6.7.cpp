static int cmp_recs(xpparam_t const *xpp,
	xrecord_t *r1, xrecord_t *r2)
{
	return r1->ha == r2->ha &&
		xdl_recmatch(r1->ptr, r1->size, r2->ptr, r2->size,
			    xpp->flags);
}