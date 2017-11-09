static int32 raw_read_int(void)
{
	char *data, buf[4];
	if (iobuf.in.size - iobuf.in.pos >= 4)
		data = perform_io(4, PIO_INPUT_AND_CONSUME);
	else
		raw_read_buf(data = buf, 4);
	return IVAL(data, 0);
}