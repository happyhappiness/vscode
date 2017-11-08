void stop_flist_forward()
{
	flist_forward_from = -1;
	io_flush(FULL_FLUSH);
}