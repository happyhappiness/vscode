int io_start_buffering_out(int f_out)
{
	if (iobuf_out) {
		assert(f_out == iobuf_f_out);
		return 0;
	}
	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
		out_of_memory("io_start_buffering_out");
	iobuf_out_cnt = 0;
	iobuf_f_out = f_out;
	return 1;
}