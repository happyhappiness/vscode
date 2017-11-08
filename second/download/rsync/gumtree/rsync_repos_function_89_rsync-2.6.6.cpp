void io_start_buffering_in(void)
{
	if (iobuf_in)
		return;
	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
		out_of_memory("io_start_buffering_in");
}