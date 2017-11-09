void start_flist_forward(int ndx)
{
	write_int(iobuf.out_fd, ndx);
	forward_flist_data = 1;
}