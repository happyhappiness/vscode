void stop_flist_forward(void)
{
	flist_forward_from = -1;
	defer_forwarding_messages--;
	io_flush(FULL_FLUSH);
}