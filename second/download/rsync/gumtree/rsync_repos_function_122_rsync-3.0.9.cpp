void io_end_buffering_in(void)
{
	if (!iobuf_in)
		return;
	free(iobuf_in);
	iobuf_in = NULL;
	iobuf_in_ndx = 0;
	iobuf_in_remaining = 0;
	iobuf_f_in = -1;
}