static int recs_match(xrecord_t **recs, long ixs, long ix, long flags)
{
	return (recs[ixs]->ha == recs[ix]->ha &&
		xdl_recmatch(recs[ixs]->ptr, recs[ixs]->size,
			     recs[ix]->ptr, recs[ix]->size,
			     flags));
}