void io_start_buffering_out(void)
{
	if (iobuf_out)
		return;
	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
		out_of_memory("io_start_buffering_out");
	iobuf_out_cnt = 0;
}