void io_end_buffering_out(void)
{
	if (!iobuf_out)
		return;
	io_flush(FULL_FLUSH);
	free(iobuf_out);
	iobuf_out = NULL;
	iobuf_f_out = -1;
}