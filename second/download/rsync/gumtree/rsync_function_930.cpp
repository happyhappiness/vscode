int io_start_buffering_in(int f_in)
{
	if (iobuf_in) {
		assert(f_in == iobuf_f_in);
		return 0;
	}
	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
		out_of_memory("io_start_buffering_in");
	iobuf_f_in = f_in;
	return 1;
}