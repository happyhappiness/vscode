static int is_blank_line(xrecord_t *rec, long flags)
{
	return xdl_blankline(rec->ptr, rec->size, flags);
}