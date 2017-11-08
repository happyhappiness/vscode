static int is_blank_line(xrecord_t **recs, long ix, long flags)
{
	return xdl_blankline(recs[ix]->ptr, recs[ix]->size, flags);
}