void start_flist_forward(int f_in)
{
	assert(iobuf_out != NULL);
	assert(iobuf_f_out == msg_fd_out);
	flist_forward_from = f_in;
	defer_forwarding_messages++;
}