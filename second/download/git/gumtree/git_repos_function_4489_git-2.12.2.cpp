static int recs_match(xrecord_t *rec1, xrecord_t *rec2, long flags)
{
	return (rec1->ha == rec2->ha &&
		xdl_recmatch(rec1->ptr, rec1->size,
			     rec2->ptr, rec2->size,
			     flags));
}